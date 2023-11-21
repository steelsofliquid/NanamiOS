# This demo is a Python demo of a console-based Calculator for NanamiOS. A few other tech demos will be made.
# You will need IDLE and/or a Python runtime to run this demo. You hopefully should be using Linux, so that's
# hopefully already dealt with! ^_^

# These Python-based demos are also kinda used to combat the around 90% C++ amount in the NanamiOS repository.
# Do they work on NanamiOS? No.

# You can also view the SuperGuide to get an understanding of why these tech demos exist. Likely, they use
# console-based technology which likely won't be used in NanamiOS.

print(" Calculator                                                            --- ---  ")
print("                                                                      -   -   - ")
print("    -           -            ----                                      -     -  ")
print("   ---  --     ---  --          -          --   --                      -   -   ")
print("    -     -     -     -      ----  -      -  - -                      -  - -  - ")
print("    -   -       -   -       -  - ---      -  -  --                    -   -   - ")
print("    -  ---      -  ---      - -   -       -  -    -                    -     -  ")
print("   -   -- -    -   -- -      --  -         --   --                      -----   ")
print("                                                                                ")
print("          D                   E                   M                   O         ")

opta = float(0)
optb = float(0)
opero = "none"
program = 1

def addition(a, b):
    res = (a + b)
    return res

def subtraction(a, b):
    res = (a - b)
    return res

def multiplication(a, b):
    res = (a * b)
    return res

def division(a, b):
    try:
        res = (a / b)
        return res
    except ZeroDivisionError:
        print("\n[Error] You cannot divide by zero.")
    except:
        print("\n[Error] Error, unspecified by developer")

while program == 1:
    opero = input("\nSelect an operator: ")
    if opero == "Add" or opero == "add" or opero == "addition" or opero == "Addition":
        try:
            opta = float(input("First number to add: "))
            optb = float(input("Second number to add: "))
            print(opta, "+", optb, "=", addition(a=opta, b=optb))
        except:
            print("\n[Error] Error, unspecified by developer")
    elif opero == "Minus" or opero == "minus" or opero == "subtraction" or opero == "Subtraction":
        try:
            opta = float(input("First number to subtract: "))
            optb = float(input("Second number to subtract: "))
            print(opta, "-", optb, "=", subtraction(a=opta, b=optb))
        except:
            print("\n[Error] Error, unspecified by developer")
    elif opero == "Times" or opero == "times" or opero == "multiplication" or opero == "Multiplication" or opero == "Multiply" or opero == "multiply":
        try:
            opta = float(input("First number to multiply: "))
            optb = float(input("Second number to multiply: "))
            print(opta, "X", optb, "=", multiplication(a=opta, b=optb))
        except:
            print("\n[Error] Error, unspecified by developer")
    elif opero == "Divide" or opero == "divide" or opero == "division" or opero == "Division":
        try:
            opta = float(input("First number to divide: "))
            optb = float(input("Second number to divide: "))
            print(opta, "/", optb, "=", division(a=opta, b=optb))
        except:
            print("\n[Error] Error, unspecified by developer")
    