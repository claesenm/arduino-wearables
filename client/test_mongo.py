import pymongo
import time

client = pymongo.MongoClient('mongodb://192.168.42.1:27017/')
db = client.arduino

print(db['arduino'])
print(db.arduino.readings.find({}))

while True:
    time.sleep(1)
    cursor = db.readings.find({})
    for doc in cursor:
        print(doc)
