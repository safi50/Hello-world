import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        stocks = db.execute("SELECT * FROM portfolio WHERE id = :id", id=session["user_id"])
        total = 0
        for stock in stocks:
            stock["name"] = lookup(stock["symbol"])["name"]
            stock["price"] = lookup(stock["symbol"])["price"]
            stock["total"] = usd(float(stock["price"]) * int(stock["shares"]))
            total = total + (float(stock["price"]) * int(stock["shares"]))
        cash = float(db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])[0]["cash"])
        total = total + cash
        return render_template('index.html', cash=usd(cash), stocks=stocks, total=usd(total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Enter a symbol!")
        shares = int(request.form.get("shares"))
        if not shares:
            return apology("Provide your shares (correctly)!")
        shares = int(shares)
        quote = lookup(symbol)
        if quote == None:
            return apology("Stock not found", 400)
        price = float(quote["price"]) * int(shares)
        cash = float(db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])[0]["cash"])

        if price > cash:
            return apology("You are not rich enough!")

        ownstock = db.execute("SELECT * FROM portfolio WHERE id = :id AND symbol = :symbol AND shares > 0", id=session["user_id"], symbol = symbol)
        if ownstock:
            updatestock = db.execute("UPDATE portfolio SET shares=(shares + :shares) WHERE id=:id AND symbol=:symbol", shares=shares, id=session["user_id"], symbol=symbol)
        else:
            newstock = db.execute("INSERT INTO portfolio (id, symbol, shares) VALUES (:id, :symbol, :shares)", id=session["user_id"], symbol=symbol, shares=int(shares))


        updatecash = db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash-price, id=session["user_id"])
        transaction = db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id=session["user_id"], symbol=symbol, shares=shares, price=price)
        flash("Your shares have been bought!")
        return redirect("/")
    else:
        return render_template("buy.html")



@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    if request.method == "POST":
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        if not check_password_hash(rows[0]["hash"], request.form.get("old")):
            return apology("Old password not correct", 400)

        if request.form.get("new1") != request.form.get("new2"):
            return apology ("New passwords are not alike")

        newpassword = db.execute("UPDATE users SET hash = :hash WHERE id = :id", hash=generate_password_hash(request.form.get("new1")), id=session["user_id"])

        if not newpassword:
            return apology("Something went wrong")

        flash("Your password has been changed!")
        return redirect("/")

    else:
        return render_template("changepassword.html")




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        transactions = db.execute("SELECT * FROM transactions WHERE id = :id", id=session["user_id"])

        for transaction in transactions:

            if transaction["price"] < 0:
                transaction["manner"] = "sold"

            else:
                transaction["manner"] = "bought"
            transaction["price"] = usd(transaction["price"])

    return render_template('history.html', transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        company = request.form.get("symbol")
        quote = lookup(company)

        if quote == None:
            return apology("Stock not found", 400)
        return render_template('quoted.html', quote = quote)

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password and confirmation do not match", 400)

        hash = generate_password_hash(request.form.get("password"))
        checkname = db.execute('SELECT * FROM users WHERE username = :username', username=request.form.get("username"))

        if checkname:
            return apology("the usrname is already taken", 400)

        else:
            newid = db.execute('INSERT INTO users (username,hash) VALUES (:username,:hash)', username=request.form.get("username"), hash=hash)

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        flash("You have been registered!")
        return redirect("/")

    else:
       return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Check whether the user's input is correct
        symbol = request.form.get("symbol")
        shares = (db.execute("SELECT shares FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)[0]["shares"])
        sharessold = (request.form.get("shares"))
        quote = lookup(symbol)
        amount = float(quote["price"]) * int(sharessold)

        if (int(shares) - int(sharessold)) < 0:
            return apology("You do not have that many shares!", 400)

        if not symbol:
            return apology("Choose a stock's symbol to sell!")

        if not shares:
            return apology("Enter an amount of shares!")

        if not sharessold:
            return apology("Something went wrong with the sold shares!")



        if int(shares) == int(sharessold):
            newshares = db.execute("DELETE FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)

        else:
            newshares = db.execute("UPDATE portfolio SET shares = (shares - :shares) WHERE id = :id AND symbol = :symbol", shares = sharessold, id=session["user_id"], symbol=symbol)

        if not newshares:
            apology('Something went wrong with the shares')
        newcash = db.execute("UPDATE users SET cash = (cash + :amount) WHERE id = :id", amount = amount, id = session["user_id"])

        if not newcash:
            apology("Something went wrong with the cash")

        transaction = db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id=session["user_id"], symbol=symbol, shares=shares, price=-amount)

        # flash("Your shares have been sold!" + str(shares) + "hallo" + str(sharessold))
        return redirect("/")

    else:
        stocks = db.execute("SELECT * FROM portfolio WHERE id = :id", id=session["user_id"])
        return render_template("sell.html", stocks=stocks)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)

# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
