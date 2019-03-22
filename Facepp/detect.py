from url import *
from process import *
import sys

if __name__ == '__main__':
    path = sys.argv[1]  # '../img/point5/1552719282.jpg'
    point = sys.argv[2]  # 5
    json = url_detect(path)
    show_jpg(path, json['faces'], point=int(point))
    infor = detect_status(json, point=int(point))
    send_result(infor)
    send_img(path)
    print(infor)
