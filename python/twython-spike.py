import time
from twython import Twython
import serial


def parse(filename, comment_char='#', separator='='):
    options = {}
    with open(filename) as f:
        for line in f:
            start = line.split(comment_char)[0]
            if separator in start:
                option, value = map(lambda x: x.strip(),
                    start.split(separator, 1))
                options[option] = value
    return options


class ArduinoSerial():
    def __init__(self, port='/dev/ttyACM0'):
        self.ser = serial.Serial(port, 9600)

    def send(self, text):
        self.ser.write(self.ascii_only(text))

    def receive(self):
        return self.ser.readline()

    @staticmethod
    def ascii_only(text):
        return ''.join(i for i in text if ord(i)<128)


def get_twitter():
    ini = parse('secrets/twitter.ini')
    key = ini['KEY']
    secret = ini['SECRET']
    tw = Twython(key, secret, oauth_version=2)
    return Twython(key, access_token=tw.obtain_access_token())


if __name__ == '__main__':
    arduino = ArduinoSerial()
    time.sleep(1.0)
    twitter = get_twitter()
    tweets = twitter.search(q='#morsetweeter')
    for status in tweets['statuses']:
        line = (status['text']).upper()+'\n'
        print line,
        arduino.send(line)
        print arduino.receive(),
