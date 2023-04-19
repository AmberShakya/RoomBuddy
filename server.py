#importing required modules
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

@app.route('/login', methods=["POST", "GET"])
def login_validation():
    if request.method == 'GET':
        return render_template('login.html')
    if request.method == 'POST':
        username = str(request.form.get('username'))
        password = hashlib.sha256(str(request.form.get('password')).encode()).hexdigest()
        cursor.execute("SELECT password FROM users WHERE username=\"" + username + "\"")
        returndata = db.fetchall()
        if (hashlibsha256(returndata[0].encode()).hexdigest() == password):
            session['login_username'] = username


@app.route('/dashboard')
def dashboard():
    user_id = session.get('login_username')
    if user_id:
        # User is logged in, show dashboard
        return "Welcome to your dashboard, user {}".format(user_id)
    else:
        # User is not logged in, redirect to login page
        return redirect(url_for('login'))

@app.route('/logout')
def logout():
    # Clear the session data and redirect to the login page
    session.clear()
    return redirect(url_for('login'))

        



@app.route('/home')
def homee():
    return ["hi", "hii"]

if __name__ == '__main__':
    app.run(port=int(os.getenv('APP_PORT')))
    #app.run(port=1234)
