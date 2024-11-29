def verify_loginid(username,password,filepath):
    count=0
    try:
        password=password+'\n'
        with open(filepath,'r') as file:
            lines=file.readlines()
            for line in lines:
                info=line.split(',')
                if username==info[0]:
                    count+=1
                    if password==info[1]:
                        print('user authentication successful')
                        return True
                    
        if count==0:
            print("the user name is not registered.")
            for i in range(3):
                password=input("create a password : ")
                if password==input('re-enter your password : '):
                    with open(filepath,'a') as filew:
                        filew.write("\n{},{}".format(username,password))
                        print("please remember your password\nuser verified")
                        break
                else:
                    print("the re-entered passsword is icorrect,")
                    continue
    except Exception:
        print(Exception)

def main():
    user_name=input("enter the login id : ")
    password=input("enter the password: ")
    verify_loginid(user_name,password,"login_info.txt")

# main()

def verify_loginid(username, password, filepath):
    count = 0
    try:
        password = password + '\n'
        with open(filepath, 'r') as file:
            lines = file.readlines()
            for line in lines:
                info = line.strip().split(',')
                if username == info[0]:
                    count += 1
                    if password.strip() == info[1]:
                        print('User authentication successful')
                        return True
        
        if count == 0:
            print("The username is not registered.")
            for i in range(3):
                new_password = input("Create a password: ")
                if new_password == input('Re-enter your password: '):
                    with open(filepath, 'a') as filew:
                        filew.write("\n{},{}".format(username, new_password))
                        print("Please remember your password\nUser verified")
                        return True
                else:
                    print("The re-entered password is incorrect.")
                    continue
    except Exception as e:
        print(f"An error occurred: {e}")
    return False

def main():
    user_name = input("Enter the login ID: ")
    password = input("Enter the password: ")
    verify_loginid(user_name, password, "login_info.txt")

main()