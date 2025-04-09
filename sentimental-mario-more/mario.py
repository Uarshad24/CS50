Height = input("Height: ")
k = 0
while k < 1:
    try:
        Height = int(Height)
        k = 1
    except:
        Height = input("Height: ")
while Height > 8 or Height < 1:
    Height = input("Height: ")
    Height = int(Height)
j = 0
while j < Height:
    i = 1
    while i < Height - j:
        print(" ", end="")
        i = i + 1
    i = 0
    while i < j + 1:
        print("#", end="")
        i = i + 1
    print("  ", end="")
    i = 0
    while i < j + 1:
        print("#", end="")
        i = i + 1
    print("")
    j = j + 1
