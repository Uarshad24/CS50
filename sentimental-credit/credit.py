Card = input("Number: ")
Number = int(Card)
Even = False
total_sum = 0
while (Number != 0):
    digit = Number % 10
    Number = int(Number / 10)
    if (Even == False):
        total_sum = digit + total_sum
        Even = True
    else:
        digit = 2 * digit

        if (digit > 9):
            digit = int(digit/10) + digit % 10
        total_sum = digit + total_sum
        Even = False
if (total_sum % 10 != 0):
    print("INVALID")
else:
    if (len(Card) == 15):
        if (int(Card[0]) == 3):
            if (int(Card[1]) == 4 or int(Card[1]) == 7):
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")
    elif (len(Card) == 13):
        if (int(Card[0]) == 4):
            print("VISA")
        else:
            print("INVALID")
    elif (len(Card) == 16):
        if (int(Card[0]) == 4):
            print("VISA")
        elif (int(Card[0]) == 5):
            if (int(Card[1]) == 1 or int(Card[1]) == 2 or int(Card[1]) == 3 or int(Card[1]) == 4 or int(Card[1]) == 5):
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
