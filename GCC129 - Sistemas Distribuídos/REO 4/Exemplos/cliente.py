import requests
import json

url = "http://localhost:5000/carros"

myResponse = requests.get(url)

if(myResponse.ok):

    jData = json.loads(myResponse.content)

    print("Foram encontrados {0} carros.".format(len(jData)))
    print("\n")
    for carro in jData:
        for atributo in carro:
            print (atributo + ": " + str(carro[atributo]))
        print("\n")
else:
  # If response code is not ok (200), print the resulting http error code with description
    myResponse.raise_for_status()