# -*- coding: utf-8 -*-
import urllib.request
import urllib.error
import time
import json

import cv2
import matplotlib.pyplot as plt


def url_detect(filepath):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/detect'
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    fr = open(filepath, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()
    # data.append('--%s' % boundary)
    # data.append('Content-Disposition: form-data; name="%s"\r\n' % 'return_landmark')
    # data.append('1')
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'return_attributes')
    data.append("headpose,facequality,eyegaze")
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
        return data
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_compare(filepath1, filepath2, face_rectangle1=None, face_rectangle2=None):
    # "top，left，width，height"
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/compare'
    # 免费
    # key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    # secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'

    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    fr = open(filepath1, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file1')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()
    data.append('--%s' % boundary)
    fr = open(filepath2, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file2')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()

    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_rectangle1')
    data.append('{},{},{},{}'.format(face_rectangle1['top'], face_rectangle1['left'], face_rectangle1['width'],
                                     face_rectangle1['height']))
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_rectangle2')
    data.append('{},{},{},{}'.format(face_rectangle2['top'], face_rectangle2['left'], face_rectangle2['width'],
                                     face_rectangle2['height']))

    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_create(outer_id):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/create'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_getfacesets():
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/getfacesets'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    # data.append('--%s' % boundary)
    # data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    # data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        return data
        # with open('data.json', 'w') as json_file:
        #     json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_getdetail(outer_id):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/getdetail'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_add(outer_id, face_tokens):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/addface'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_tokens')
    data.append(face_tokens)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_search(filepath, outer_id):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/search'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)

    data.append('--%s' % boundary)
    fr = open(filepath, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        return data
        # with open('data.json', 'w') as json_file:
        #     json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def show_jpg(path, json, point):
    jpg = cv2.imread(path)  # ('../img/point1/1552637350.jpg')
    # jpg = jpg[:, :, ::-1]

    # plt.show()
    # plt.imshow(jpg)

    if point == 1:
        y_line = 421
        x_line = 950
        cv2.line(jpg, (0, y_line), (1919, y_line), (0, 0, 255), thickness=5)
        cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 2:
        y_line = 471
        x_line = 950
        cv2.line(jpg, (0, y_line), (1919, y_line), (0, 0, 255), thickness=5)
        cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 3:
        y1_line = 350
        y2_line = 700
        x_line = 950
        cv2.line(jpg, (0, y1_line), (1919, y1_line), (0, 0, 255), thickness=5)
        cv2.line(jpg, (0, y2_line), (1919, y2_line), (0, 0, 255), thickness=5)
        cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y1_line, 0, 1919, colors='r')
        # plt.hlines(y2_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 4:
        y1_line = 350
        y2_line = 700
        x_line = 1050
        cv2.line(jpg, (0, y1_line), (1919, y1_line), (0, 0, 255), thickness=5)
        cv2.line(jpg, (0, y2_line), (1919, y2_line), (0, 0, 255), thickness=5)
        cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y1_line, 0, 1919, colors='r')
        # plt.hlines(y2_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    # elif point == 5:

    for index, face in enumerate(json['faces']):
        rectangle = face['face_rectangle']
        cv2.rectangle(jpg, (rectangle['left'], rectangle['top']),
                      (rectangle['left'] + rectangle['width'], rectangle['top'] + rectangle['height']), (0, 0, 255),
                      thickness=5)
        # plt.hlines(rectangle['top'], rectangle['left'], rectangle['left'] + rectangle['width'], colors='r')
        # plt.hlines(rectangle['top'] + rectangle['height'], rectangle['left'], rectangle['left'] + rectangle['width'],
        #            colors='r')
        # plt.vlines(rectangle['left'], rectangle['top'], rectangle['top'] + rectangle['height'], colors='r')
        # plt.vlines(rectangle['left'] + rectangle['width'], rectangle['top'], rectangle['top'] + rectangle['height'],
        #            colors='r')

    # plt.savefig('1.jpg')
    # cv2.imshow("", jpg)
    cv2.imwrite('2.jpg', jpg)


def rollcall(json, point):
    inf_set = dict()
    if point == 1:
        y_line = 421
        x_line = 950
    elif point == 2:
        y_line = 471
        x_line = 950
    elif point == 3:
        y1_line = 350
        y2_line = 700
        x_line = 950

    for index, face in enumerate(json['faces']):
        rectangle = face['face_rectangle']
        center_x = rectangle['left'] + rectangle['width'] / 2
        center_y = rectangle['top'] + rectangle['height'] / 2
        if point == 1:
            if center_y > y_line:
                if center_x < x_line:
                    # 1号座位
                    inf_set.update({'1': json['results'][index]['face_token']})
                else:
                    # 2号座位
                    inf_set.update({'2': json['results'][index]['face_token']})
            else:
                if center_x < x_line:
                    # 3号座位
                    inf_set.update({'3': json['results'][index]['face_token']})
                else:
                    # 4号座位
                    inf_set.update({'4': json['results'][index]['face_token']})
        elif point == 2:
            if center_y > y_line:
                if center_x < x_line:
                    # 5号座位
                    inf_set.update({'5': json['results'][index]['face_token']})
                else:
                    # 6号座位
                    inf_set.update({'6': json['results'][index]['face_token']})
            else:
                if center_x < x_line:
                    # 7号座位
                    inf_set.update({'7': json['results'][index]['face_token']})
                else:
                    # 8号座位
                    inf_set.update({'8': json['results'][index]['face_token']})
        elif point == 3:
            if center_y < y1_line:
                if center_x < x_line:
                    # 9号座位
                    inf_set.update({'9': json['results'][index]['face_token']})
                else:
                    # 10号座位
                    inf_set.update({'10': json['results'][index]['face_token']})
            elif center_y < y2_line:
                if center_x < x_line:
                    # 11号座位
                    inf_set.update({'11': json['results'][index]['face_token']})
                else:
                    # 12号座位
                    inf_set.update({'12': json['results'][index]['face_token']})
            else:
                if center_x < x_line:
                    # 13号座位
                    inf_set.update({'13': json['results'][index]['face_token']})
                else:
                    # 14号座位
                    inf_set.update({'14': json['results'][index]['face_token']})
        elif point == 4:
            if center_y < y1_line:
                if center_x < x_line:
                    # 15号座位
                    inf_set.update({'15': json['results'][index]['face_token']})
                else:
                    # 16号座位
                    inf_set.update({'16': json['results'][index]['face_token']})
            elif center_y < y2_line:
                if center_x < x_line:
                    # 17号座位
                    inf_set.update({'17': json['results'][index]['face_token']})
                else:
                    # 18号座位
                    inf_set.update({'18': json['results'][index]['face_token']})
            else:
                if center_x < x_line:
                    # 19号座位
                    inf_set.update({'19': json['results'][index]['face_token']})
                else:
                    # 20号座位
                    inf_set.update({'20': json['results'][index]['face_token']})

    return inf_set


if __name__ == '__main__':
    # pitch_angle越大，低头越严重，大于10就认为是低头
    # facequality越大那么脸越清晰，越能证明抬头（不太准）
    # vector_z_component越大越认真，大于0.9就认为是向上
    # json = url_detect('../img/point1/1552637350.jpg')
    # face_rectangle1 = {"width": 181, "top": 155, "left": 94, "height": 181}
    # face_rectangle2 = {"width": 121, "top": 205, "left": 449, "height": 121}
    # url_compare('../img/t1.jpg', '../img/t4.jpg', face_rectangle1, face_rectangle2)

    # url_faceset_create(outer_id='faceset_test')
    # json = url_faceset_getfacesets()
    # url_faceset_getdetail(outer_id='faceset_test')
    # url_faceset_add(outer_id='faceset_test',
    #                 face_tokens='32f4b716dccb632139d33e3b0fbe99a9,2476e3a308dafd3ac987cc237836e9b7')  # 佟丽娅、吴京的face_token
    # json = url_search('../img/t2.jpg', outer_id='faceset_test')
    infor = None
    path = '../img/point5/1552719274.jpg'
    json = url_search(path, outer_id='faceset_classmate')
    show_jpg(path, json, point=5)
    infor = rollcall(json, point=5)
    exit()
