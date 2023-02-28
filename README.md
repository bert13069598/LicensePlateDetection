# LicensePlateDetection
||version|
|:---:|:---:|
|python|3.9|
|kernel|6.0.12|

## Data resource
[Plate Detection](https://www.kaggle.com/datasets/andrewmvd/car-plate-detection)

[Number Detection](https://aihub.or.kr/unitysearch/list.do?kwd=%EC%9E%90%EB%8F%99%EC%B0%A8)
데이터셋 > 자동차 차종/연식/번호판 인식용 영상

## Prerequisite
```bash
chmod +x install_cv4.5.1_rasbian.sh
chmod +x install_tensorflowlite2.6.0_rasbian.sh
./install_cv4.5.1_rasbian.sh
./install_tensorflowlite2.6.0_rasbian.sh
pip3 install https://github.com/google-coral/pycoral/releases/download/v2.0.0/tflite_runtime-2.5.0.post1-cp39-cp39-linux_armv7l.whl
```

## Model train
[tensorflow tutorial](https://colab.research.google.com/github/EdjeElectronics/TensorFlow-Lite-Object-Detection-on-Android-and-Raspberry-Pi/blob/master/Train_TFLite2_Object_Detction_Model.ipynb#scrollTo=RDQrtQhvC3oG)

## Start program with inserting module
```bash
sudo insmod gpio_driver.ko
sudo insmod seg_driver.ko
chmod +x termproject_v3
sudo ./termproject_v3
```

## Input
keyboard input = 'c'

<img src="https://github.com/bert13069598/LicensePlateDetection/blob/master/test_license2.png">

## Result
keyboard input = 'd'

python3 [TFLite_detection_image_license.py](https://github.com/bert13069598/LicensePlateDetection/blob/master/TFLite_detection_image_license.py) --modeldir= --labels=[labelmap.txt](https://github.com/bert13069598/LicensePlateDetection/blob/master/labelmap.txt) --image=test_license2.png --save_results --noshow_results --graph=[detect_plate.tflite](https://github.com/bert13069598/LicensePlateDetection/blob/master/detect_plate.tflite)

<img src="https://github.com/bert13069598/LicensePlateDetection/blob/master/results/test_license2.png">

##
python3 [TFLite_detection_image.py](https://github.com/bert13069598/LicensePlateDetection/blob/master/TFLite_detection_image.py) --modeldir= --labels=[labelmap2.txt](https://github.com/bert13069598/LicensePlateDetection/blob/master/labelmap2.txt) --image=./results/test_license2_crop0.png --save_results --noshow_results --graph=[detect_number2.tflite](https://github.com/bert13069598/LicensePlateDetection/blob/master/detect_number2.tflite)

<img src="https://github.com/bert13069598/LicensePlateDetection/blob/master/results/test_license2_crop0.png">

## Quit program with removing module
keyborad input = 'q'
```bash
sudo rmmod gpio_driver.ko
sudo rmmod seg_driver.ko
```
