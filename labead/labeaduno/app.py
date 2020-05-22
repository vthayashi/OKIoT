# python app.py
# https://github.com/arshadansari27/flask-image-server/blob/master/app.py
#http://zetcode.com/python/flask/

import serial

from flask import Flask, send_file
from flask import render_template
from flask import request

ser = serial.Serial('COM8', baudrate=57600, timeout=1)

app = Flask(__name__)

@app.route('/')
def hello():
    return render_template('index.html')

@app.route('/scope')
def scope():
    return render_template('scope.html')

@app.route('/js')
def js():
    data="{}"
    command = request.query_string
    ser.write(command)
    ser.write(b'\r')
    data = ser.readline()
    return data

if __name__ == '__main__':
    app.run()

ser.close()
