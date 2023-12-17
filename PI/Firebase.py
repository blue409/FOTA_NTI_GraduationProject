def main():
  import pyrebase
  import time
  import os

  #all the data needed to get access to the realtime Db
  config = {
    "apiKey": "AIzaSyDTxNmxDwasUTWRnRx2ab-w7kOMCfe83XE",
    "authDomain": "fota-test-48f52.firebaseapp.com",
    "databaseURL": "https://fota-test-48f52-default-rtdb.europe-west1.firebasedatabase.app/",
    "storageBucket": "fota-test-48f52.appspot.com",
    "serviceAccount": "fota-test-48f52-firebase-adminsdk-yyf59-d16aef84bc.json"
  }


  #initilize the connection using the config data 
  firebase = pyrebase.initialize_app(config)

  # ask for authentication
  auth = firebase.auth()

  # Log the user in using Email and password
  user = auth.sign_in_with_email_and_password("ahmedosama9714@gmail.com", "123456789")

  # Get a reference to the database service
  db = firebase.database()

  NewHexFetchRequest=db.child("Fetch").get()
  FlashExsitingHexCommand=db.child("Flash").get()

  if(NewHexFetchRequest.val()):

    # Pass the user's idToken to the push method
    results = db.child("MY_HEX").get()

    #if not created create a text file My_Hex.txt and open it in write mode
    HexFile=open(r"My_Hex.txt", "w")

    #right all the hex file content in the My_Hex.txt file
    HexFile.write(str(results.val()))

    #close the file after finishing writing
    HexFile.close()

    NewHexFetchRequest.val=0

    db.child("DoneFetching").push(0)

    os.system('sudo python ./UARTSingleRecord.py Arg')

    time.sleep(1)
  elif(FlashExsitingHexCommand.val() and (not(NewHexFetchRequest.val()))):
    os.system('sudo python ./UARTSingleRecord.py Arg')
    db.child("DoneFlashing").push(0)

    

if __name__ == "__main__":
    main()

