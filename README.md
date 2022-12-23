# LicensePlateDetection
### python version
3.9

### kernel version
6.0.12

## data resource
[Plate Detection](https://www.kaggle.com/datasets/andrewmvd/car-plate-detection)

[Number Detection](https://aihub.or.kr/unitysearch/list.do?kwd=%EC%9E%90%EB%8F%99%EC%B0%A8)
자동차 차종/연식/번호판 인식용 영상이미지

## prerequisite
```bash
chmod +x install_cv4.5.1_rasbian.sh
chmod +x install_tensorflowlite2.6.0_rasbian.sh
./install_cv4.5.1_rasbian.sh
./install_tensorflowlite2.6.0_rasbian.sh
pip3 install https://github.com/google-coral/pycoral/releases/download/v2.0.0/tflite_runtime-2.5.0.post1-cp39-cp39-linux_armv7l.whl
```
## start program with inserting module
```bash
sudo insmod gpio_driver.ko
sudo insmod seg_driver.ko
chmod +x termproject_v3
sudo ./termproject_v3
```

## input
keyboard input = 'c'

<img src="https://github.com/bert13069598/LicensePlateDetection/blob/master/test_license2.png">

## result
keyboard input = 'd'

[TFLite_detection_image_license.py](https://github.com/bert13069598/LicensePlateDetection/blob/master/TFLite_detection_image_license.py)

[detect_plate.tflite](https://github.com/bert13069598/LicensePlateDetection/blob/master/detect_plate.tflite)

[labelmap.txt](https://github.com/bert13069598/LicensePlateDetection/blob/master/labelmap.txt)

<img src="https://github.com/bert13069598/LicensePlateDetection/blob/master/results/test_license2.png">

##

[TFLite_detection_image.py](https://github.com/bert13069598/LicensePlateDetection/blob/master/TFLite_detection_image.py)

[detect_number2.tflite](https://github.com/bert13069598/LicensePlateDetection/blob/master/detect_number2.tflite)

[labelmap2.txt](https://github.com/bert13069598/LicensePlateDetection/blob/master/labelmap2.txt)

<img src="https://github.com/bert13069598/LicensePlateDetection/blob/master/results/test_license2_crop0.png">

## quit program with removing module
keyborad input = 'q'
```bash
sudo rmmod gpio_driver.ko
sudo rmmod seg_driver.ko
```
