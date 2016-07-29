#!/usr/bin/python3.4
import serial
import time
import json
import pymongo


# http://stackoverflow.com/a/21300518


if __name__ == '__main__':

    # set up database
    c = pymongo.MongoClient()
    db = c['arduino']
    # remove all prior readings, might contain wrong sensors etc.
    db.drop_collection('readings')

    readings = {}

    try:
        serial_dev = '/dev/ttyACM0'
        baud = 115200

        print('Attempting to make serial connection to %s.' % serial_dev)
        while True:
            try:
                # make all reads blocking
                ser = serial.Serial(serial_dev, baud, timeout = None)
                print('Serial connection to %s established.' % serial_dev)
                break
            except serial.serialutil.SerialException:
                print('Unable to connect, retrying...')
                time.sleep(1)

        # get initial non-borking reading
        while True:
            try:
                state = ser.readline()
                state = state.decode("utf-8")
                #print(state)
                if len(state) and state[0] == "{":
                    readings = json.loads(state)
                    break
            except ValueError:
                pass

        # main loop
        while True:
            #print('Reading from Arduino...')
            state = ser.readline()
            state = state.decode("utf-8")
            #print(state)
            if len(state) and state[0] == "{":
                #print(state)
                readings = json.loads(state)
                print(readings)

                collection = db['readings']

                readings['timestamp'] = time.time()
                readings['_id'] = 1
                db.readings.replace_one({'_id': 1}, readings, upsert=True)

    except KeyboardInterrupt:
        print('^C received, shutting down')
        c.close()
