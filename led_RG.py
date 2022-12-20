import RPi.GPIO as GPIO     # 라즈베리파이 GPIO 관련 모듈을 불러옴
import time                 # 시간관련 모듈을 불러옴
import argparse

GPIO.setmode(GPIO.BCM)      # GPIO 핀들의 번호를 지정하는 규칙 설정

parser = argparse.ArgumentParser()
parser.add_argument('--isSame', help='compare resultNum with license', required=True, default=False)
args = parser.parse_args()


isSame = int(args.isSame)

### 이부분은 아두이노 코딩의 setup()에 해당합니다
LED_G_pin = 5                     # Green
LED_R_pin = 6                     # Red
servo_pin = 18                    # Servo
GPIO.setup(LED_G_pin, GPIO.OUT)   # LED 핀을 출력으로 설정
GPIO.setup(LED_R_pin, GPIO.OUT)   # LED 핀을 출력으로 설정
GPIO.setup(servo_pin, GPIO.OUT)   # Set Servo pin output
pwm = GPIO.PWM(servo_pin, 50)  # 50Hz (서보모터 PWM 동작을 위한 주파수)
pwm.start(3.0) #서보의 0도 위치(0.6ms)이동:값 3.0은 pwm주기인 20ms의 3%를 의미하므로,0.6ms됨.


print('isSame :',isSame)

if isSame == 1:
    print("registered number!")

    GPIO.output(LED_R_pin, GPIO.LOW)
    GPIO.output(LED_G_pin, GPIO.HIGH)
    # time.sleep(3)

    for t_high in range(60, 100):
        pwm.ChangeDutyCycle(t_high/10.0)   # 서보모터를 0도로 회전(이동)
        time.sleep(0.2)             # 서보 모터가 이동할 시간을 줌
    t_high=0
               
    GPIO.cleanup()

    pwm.ChangeDutyCycle(0.0)
    pwm.stop()
else:
    print("unregistered number!")

    GPIO.output(LED_G_pin, GPIO.LOW)
    GPIO.output(LED_R_pin, GPIO.HIGH)
    # time.sleep(3)   

    for t_high in range(60, 100):
        pwm.ChangeDutyCycle((150-t_high)/10.0)   # 서보모터를 0도로 회전(이동)
        time.sleep(0.2)             # 서보 모터가 이동할 시간을 줌
    t_high=0


    GPIO.cleanup()

    pwm.ChangeDutyCycle(0.0)
    pwm.stop()


