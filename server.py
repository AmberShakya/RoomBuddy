import os
from wsgiref.simple_server import make_server
from flask import Flask, jsonify, make_response, render_template, request, request_started
from dotenv import load_dotenv
import mysql.connector

load_dotenv()
app = Flask(__name__)
db = mysql.connector.connect(host=os.getenv('DB_host'),user=os.getenv("DB_user"),password=os.getenv("DB_password"),database=os.getenv("DB_name"))
cursor = db.cursor()

cursor.execute("CREATE TABLE IF NOT EXISTS()")



@app.route('/')
def home():
    return render_template('index.html')



if __name__ == '__main__':
    app.run(port=int(os.getenv('APP_PORT')))
    #app.run(port=1234)
