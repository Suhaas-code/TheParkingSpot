import smtplib

from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

def SEND():
    email_add_receiver = "gautamvhavle@icloud.com"
    email_add_sender = "theparkingspotog@gmail.com" # senders Gmail id over here
    pass_sender = "ILoveTech1234" # senders Gmail's pass_senderword over here

    server = smtplib.SMTP(host='smtp.gmail.com', port=587)
    server.ehlo()
    server.starttls()
    server.login(email_add_sender, pass_sender)

    msg = MIMEMultipart('alternative')
    EmailContent = '''<html>

<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Comfortaa:wght@700&family=Lustria&family=Manrope&family=Source+Sans+Pro&display=swap" rel="stylesheet">

<h1 style="color: white"> The Parking Spot </h1>
<hr>

<style>
    h1 {
        color: white;
        text-align: center;
        font-size: 40px;
        font-family: 'Comfortaa', cursive;
    }

    h2 {
        color: black;
        font-size: 30px;
        font-family: 'Lustria', serif;
    }

    h2.location {
        color: white;
        font-size: 30px;
        margin-right: auto;
        margin-left: auto;
        width: 21%;
        text-align: center;
        font-family: 'Manrope', sans-serif;
    }

    h2.carModel {
        color: lightgreen;
        font-size: 30px;
        margin-right: auto;
        margin-left: auto;
        width: 21%;
        text-align: center;
        font-family: 'Comfortaa', cursive;
    }

    div.paras {
        color: pink;
        font-size: 20px;
        font-family: 'Roboto Condensed', sans-serif;
    }
</style>

<body
    style="background-image: url(https://images.unsplash.com/photo-1590674899484-d5640e854abe?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1167&q=80); backdrop-filter: blur(4px);">

    <div class="paras">
        <p>Hi,</p>
        <p>Here are your vehicle parking details</p>
    </div>

    <h2 class="location">B1-012</h2>
    <h2 class="carModel">Rolls Royce Phantom</h2>

    <!-- <h4 style="color: white"> Parking Successful </h4> -->
    <p style="color: white"> Parking Successful </p>

</body>

</html>
'''

    HTML = MIMEText(EmailContent, 'html')
    msg.attach(HTML)

    msg['Subject'] = 'The Parking Spot'
    msg['From'] = email_add_sender
    msg['To'] = email_add_receiver

    server.sendmail(email_add_sender, email_add_receiver, msg.as_string())
    server.quit()

    print("Email sent")
