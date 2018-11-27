from flask import Flask, render_template

app=Flask(__name__)

@app.route('/') #IP/

def index():
    return render_template('index.html')

@app.route('/cakes') #IP/cakes
def cakes():
    return 'Yummy cakes!'

@app.route('/hello/<name>')
def hello(name):
    return render_template('page.html', name=name)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
    
#Se der erron0 98:
    #ir ao terminal
    # ps -fA | grep python
    # ver o número do processo com o nome deste script
    # kill número do processo (exp: kill 3500)
    
