from time import*
from calendar import*
from random import*
from os import*
from sys import*
from platform import*


sleep(1)

kitsuneosver = [0, 00, 1, 1] # Guide: Major, Minor, Release, Build. Example: 0.00.1.1 (Major.Minor.Release.Build)

def haltkitsune(code):
    print("KitsuneOS")
    print("Version", kitsuneosver[0], kitsuneosver[1], kitsuneosver[2], kitsuneosver[3], sep=".")

    print("\nSystem Halted due to error", code, ". Refer to the manual for more information.")
    raise Exception("KitsuneOS Error")


users = ["default", "guest"] # section 1 of the user system.
passwords = ["kitsuneos", "12345"]

loggedin_a = "boot"
loggedin_b = "null"
session = 0

comman = ""

print("KitsuneOS Non-Bootable Ideas Prototype\nVersion", kitsuneosver[0], kitsuneosver[1], kitsuneosver[2], kitsuneosver[3], "<null> Project Codename \"Nanami\" - Date 2023 October 25th", sep=".")
print(processor())

sleep(3.22)

loggedin_a = input("\n-- Log in to KitsuneOS --\nUsername:")
if loggedin_a == "boot":
    haltkitsune(code="0x00 INVALID_USER_OPTION")
else:
    for i in range(len(users)):
        if loggedin_a == users[i]:
            session = (session + 0.5)
            break
    if session == 0:
        haltkitsune(code="0x01 LOGIN_FAILURE")
    
    
loggedin_b = input("Password: ")
if loggedin_b == "null":
    haltkitsune(code="0x00 INVALID_USER_OPTION")
else:
    for i in range(len(passwords)):
        if loggedin_b == passwords[i]:
            session = (session + 0.5)
            break
    if session == 0.5:
        haltkitsune(code="0x01 LOGIN_FAILURE *Tip! The guest account password is 12345!")

while session == 1:
    comman = input("V/")
    if comman == "WhoAmI?":
        print(loggedin_a)
    elif comman == "Ver":
        print("KitsuneOS\nVersion", kitsuneosver[0], kitsuneosver[1], kitsuneosver[2], kitsuneosver[3], "Project \"Nanami\"", sep=".")
    elif comman == "KillAssist!!":
        print("You can shut off the program by performing a Python Keyboard Interrupt (Ctrl+C).")
    elif comman == "UserManager":
        usermanager_option = input("--Options--\n\"view\": View all users stored in this.\n\"add\": Add a new user and password.\n\"remove\": Delete a user account.\n\"edit\": Edit a user account.\n\"swap\": Change to another user account.\nSelect an option: ")
        if usermanager_option == "view":
            for i in range(len(users)):
                print("Username:    ", users[i], "Password:      ", passwords[i])
                sleep(0.01)
        elif usermanager_option == "add":
            usermanager_addtotheus = input("Choose a username:  ")
            usermanager_addtothepa = input("Choose a passowrd:  ")
            users.append(usermanager_addtotheus)
            passwords.append(usermanager_addtothepa)

        elif usermanager_option == "remove":
            print("This is a demo, non-bootable/non-operational prototype of KitsuneOS.\nAs such, you cannot remove a user account.")
        
        elif usermanager_option == "edit":
            print("This is a demo, non-bootable/non-operational prototype of KitsuneOS.\nAs such, you cannot edit a user account.")
        
        elif usermanager_option == "swap":
            print("This is a demo, non-bootable/non-operational prototype of KitsuneOS.\nYou can't change the user account.")
        
        else:
            print("Please run the command and select a valid option.")
        
    elif comman == "ProgramList":
        print("-- Program List --")
        sleep(0.01)
        print("WhoAmI?      Ver         KillAssist!!    UserManager")
        sleep(0.01)
        print("ProgramList  SystemInfo  Calendar        RollDice")
    
    elif comman == "SystemInfo":
        print(platform())
    
    elif comman == "Calendar":
        kitsucal = int(input("Chooce the year you want to view the calendar for: "))
        print(calendar(theyear=kitsucal))
    
    elif comman == "RollDice":
        print(randint(1, 6))
    
    else:
        print ("The command or program you tried to start doesn't exist. To get a list of programs/commands you can use, type \"ProgramList\" EXACTLY.")
    
    sleep(0.77)


print("System exit. This prototype will reset for the next use.")
sleep(5)