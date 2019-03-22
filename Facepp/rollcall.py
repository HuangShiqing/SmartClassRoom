from url import *
from process import *
import sys

if __name__ == '__main__':
    path = sys.argv[1]  # '../img/point5/1552719282.jpg'
    point = sys.argv[2]  # 5

    search_result, faces = url_search_all(path, outer_id='faceset_classmate')
    show_jpg(path, faces, point=int(point))
    infor = rollcall(faces, search_result, point=int(point))
    send_result(infor)
    print(infor)
