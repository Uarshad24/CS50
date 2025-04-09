import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

db.execute("CREATE TABLE IF NOT EXISTS portfolio ( user_id TEXT, stock_symbol TEXT, stock_price REAL, stock_quantity REAL, stock_value REAL, CONSTRAINT unique_user_stock UNIQUE (user_id, stock_symbol))")
db.execute("CREATE TABLE IF NOT EXISTS orders ( user_id TEXT, stock_symbol TEXT, stock_price REAL, stock_quantity REAL, transaction_type TEXT, date_time TEXT )")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    Username = (db.execute("SELECT username FROM users WHERE id = ?", session["user_id"]))
    Username = Username[0]['username']
    cash = (db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"]))
    cash = cash[0]['cash']
    stock_value = 0
    portfolio = (db.execute("SELECT * FROM portfolio WHERE user_id = ?", session["user_id"]))
    for stock in portfolio:
        stock_value = stock_value + stock["stock_price"] * stock["stock_quantity"]
    total = cash + stock_value
    return render_template("index.html", Username=Username, portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("write symbol you want to buy", 400)
        if not request.form.get("shares"):
            return apology("write No of shares you want to buy", 400)
        try:
            if int(request.form.get("shares")) <= 0:
                return apology("No of shares must be a positive number", 400)
        except:
            return apology("Enter an interger", 400)
        buy_dict = {}
        try:
            buy_dict.update(lookup(request.form.get("symbol")))
        except:
            return apology("symbol not exist", 400)
        No_of_shares = request.form.get("shares")
        price = buy_dict["price"]
        cash = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])

        Total_price = int(No_of_shares) * int(price)

        if cash[0]['cash'] < Total_price:
            return apology("Can not afford the No of shares at the current price", 403)
        upd_cash = cash[0]['cash'] - Total_price
        db.execute("UPDATE users SET cash = ?  WHERE id = ?", upd_cash, session["user_id"])
        date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        try:
            db.execute("INSERT INTO portfolio (user_id , stock_symbol, stock_price, stock_quantity, stock_value) VALUES(?,?,?,?,?)",
                       session["user_id"], buy_dict["symbol"], buy_dict["price"], No_of_shares, Total_price)

        except:
            db.execute("UPDATE portfolio SET stock_quantity = stock_quantity + ? , stock_value = stock_value + ?   WHERE stock_symbol = ? AND user_id = ?",
                       No_of_shares, Total_price, buy_dict["symbol"], session["user_id"])
        db.execute("INSERT INTO orders (user_id , stock_symbol, stock_price, stock_quantity, transaction_type, date_time) VALUES(?,?,?,?,'buy',?)",
                   session["user_id"], buy_dict["symbol"], buy_dict["price"], No_of_shares, date)
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    Username = (db.execute("SELECT username FROM users WHERE id = ?", session["user_id"]))
    Username = Username[0]['username']
    transactions = (db.execute(
        "SELECT stock_symbol, stock_price, stock_quantity, transaction_type, date_time FROM orders WHERE user_id = ?", session["user_id"]))

    return render_template("history.html", Username=Username, transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("write symbol", 400)
        quote_dict = lookup(request.form.get("symbol"))
        if quote_dict == None:
            return apology("invalid ticker", 400)
        quote = float(quote_dict['price'])
        return render_template("quoted.html", dict_values=quote_dict, quote=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        if not request.form.get("password"):
            return apology("must provide passowrd", 400)
        if not request.form.get("confirmation"):
            return apology("must provide confirm passowrd", 400)
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Confirm password doesn't match", 400)
        # Query database for username
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get(
                "username"), generate_password_hash(request.form.get("password")))
        except:
            return apology("username already exists", 400)

        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("write symbol you want to buy", 403)
        if not request.form.get("shares"):
            return apology("write No of shares you want to buy", 403)
        try:
            if int(request.form.get("shares")) <= 0:
                return apology("No of shares must be a positive number", 403)
        except:
            return apology("No of shares must be an integer", 403)

        No_of_shares = float(request.form.get("shares"))
        sell_dict = lookup(request.form.get("symbol"))
        stock_quantity = db.execute(
            "SELECT stock_quantity  FROM portfolio WHERE stock_symbol = ? AND user_id = ?", sell_dict["symbol"], session["user_id"])

        if stock_quantity[0]['stock_quantity'] < No_of_shares:
            return apology("Not enough shares to sell", 400)

        price = float(sell_dict["price"])

        cash = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])
        Total_price = No_of_shares * price
        upd_cash = cash[0]['cash'] + Total_price
        date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        db.execute("UPDATE users SET cash = ?  WHERE id = ?", upd_cash, session["user_id"])
        upd_stock = stock_quantity[0]['stock_quantity'] - No_of_shares
        db.execute("UPDATE portfolio SET stock_quantity = ? , stock_value = stock_value - ?   WHERE stock_symbol = ? AND user_id = ?",
                   upd_stock, Total_price, sell_dict["symbol"], session["user_id"])
        db.execute("INSERT INTO orders (user_id , stock_symbol, stock_price, stock_quantity, transaction_type, date_time) VALUES(?,?,?,?,'sell',?)",
                   session["user_id"], sell_dict["symbol"], sell_dict["price"], No_of_shares, date)
        return redirect("/")

    stocks = db.execute("SELECT stock_symbol FROM portfolio WHERE user_id = ?",  session["user_id"])
    return render_template("sell.html", stocks=stocks)
