text = input("Text: ")
sentences = 0
words = 1
letters = 0

for i in text:
    if i == "." or i == "?" or i == "!":
        sentences = sentences + 1

    elif i.isalpha():
        letters = letters + 1

    elif i == " ":
        words = words + 1
L = (letters / words) * 100
S = (sentences / words) * 100
index = int(round((0.0588 * L) - (0.296 * S) - 15.8))

if (index < 1):
    print("Before Grade 1")
elif (index > 0 and index <= 16):
    print("Grade ", index)
else:
    print("Grade 16+")
