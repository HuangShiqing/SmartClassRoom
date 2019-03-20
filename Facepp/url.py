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
        # print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        # with open('data.json', 'w') as json_file:
        #     json_file.write(json.dumps(data))
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
        return data
        # with open('data.json', 'w') as json_file:
        #     json_file.write(json.dumps(data))
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


def url_search(filepath, face_token, outer_id):
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
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_token')
    data.append(face_token)
    data.append('--%s' % boundary)
    if filepath != None:
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


def url_search_all(file_path, outer_id):
    json = url_detect(file_path)
    faces = json['faces']
    result = list()
    for face in faces:
        json = url_search(face_token=face['face_token'], filepath=None, outer_id=outer_id)
        result.append(json['results'][0])
    return result, faces


def show_jpg(path, json, point):
    jpg = cv2.imread(path)  # ('../img/point1/1552637350.jpg')
    # jpg = jpg[:, :, ::-1]

    # plt.show()
    # plt.imshow(jpg)

    if point == 1:
        r11_x = 0
        r11_y = 344
        r12_x = 613
        r12_y = 1013
        cv2.rectangle(jpg, (r11_x, r11_y), (r12_x, r12_y), color=(0, 255, 0), thickness=5)

        r21_x = 759
        r21_y = 403
        r22_x = 1431
        r22_y = 1075
        cv2.rectangle(jpg, (r21_x, r21_y), (r22_x, r22_y), color=(0, 255, 0), thickness=5)

        r31_x = 1072
        r31_y = 0
        r32_x = 1630
        r32_y = 471
        cv2.rectangle(jpg, (r31_x, r31_y), (r32_x, r32_y), color=(0, 255, 0), thickness=5)

        r41_x = 323
        r41_y = 0
        r42_x = 869
        r42_y = 437
        cv2.rectangle(jpg, (r41_x, r41_y), (r42_x, r42_y), color=(0, 255, 0), thickness=5)
        # y_line = 421
        # x_line = 950
        # cv2.line(jpg, (0, y_line), (1919, y_line), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 2:
        r11_x = 328
        r11_y = 456
        r12_x = 1012
        r12_y = 1080
        cv2.rectangle(jpg, (r11_x, r11_y), (r12_x, r12_y), color=(0, 255, 0), thickness=5)

        r21_x = 1288
        r21_y = 349
        r22_x = 1920
        r22_y = 1042
        cv2.rectangle(jpg, (r21_x, r21_y), (r22_x, r22_y), color=(0, 255, 0), thickness=5)

        r31_x = 1127
        r31_y = 0
        r32_x = 1679
        r32_y = 457
        cv2.rectangle(jpg, (r31_x, r31_y), (r32_x, r32_y), color=(0, 255, 0), thickness=5)

        r41_x = 263
        r41_y = 0
        r42_x = 833
        r42_y = 565
        cv2.rectangle(jpg, (r41_x, r41_y), (r42_x, r42_y), color=(0, 255, 0), thickness=5)
        # y_line = 471
        # x_line = 950
        # cv2.line(jpg, (0, y_line), (1919, y_line), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 3:

        r11_x = 1211
        r11_y = 574
        r12_x = 1681
        r12_y = 1044
        cv2.rectangle(jpg, (r11_x, r11_y), (r12_x, r12_y), color=(0, 255, 0), thickness=5)

        r21_x = 216
        r21_y = 647
        r22_x = 692
        r22_y = 1080
        cv2.rectangle(jpg, (r21_x, r21_y), (r22_x, r22_y), color=(0, 255, 0), thickness=5)

        r31_x = 1185
        r31_y = 224
        r32_x = 1583
        r32_y = 622
        cv2.rectangle(jpg, (r31_x, r31_y), (r32_x, r32_y), color=(0, 255, 0), thickness=5)

        r41_x = 385
        r41_y = 302
        r42_x = 787
        r42_y = 704
        cv2.rectangle(jpg, (r41_x, r41_y), (r42_x, r42_y), color=(0, 255, 0), thickness=5)

        r51_x = 1141
        r51_y = 0
        r52_x = 1489
        r52_y = 330
        cv2.rectangle(jpg, (r51_x, r51_y), (r52_x, r52_y), color=(0, 255, 0), thickness=5)

        r61_x = 419
        r61_y = 13
        r62_x = 761
        r62_y = 355
        cv2.rectangle(jpg, (r61_x, r61_y), (r62_x, r62_y), color=(0, 255, 0), thickness=5)
        # y1_line = 350
        # y2_line = 700
        # x_line = 950
        # cv2.line(jpg, (0, y1_line), (1919, y1_line), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (0, y2_line), (1919, y2_line), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y1_line, 0, 1919, colors='r')
        # plt.hlines(y2_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 4:
        r11_x = 1135
        r11_y = 599
        r12_x = 1599
        r12_y = 1063
        cv2.rectangle(jpg, (r11_x, r11_y), (r12_x, r12_y), color=(0, 255, 0), thickness=5)

        r21_x = 0
        r21_y = 624
        r22_x = 427
        r22_y = 1068
        cv2.rectangle(jpg, (r21_x, r21_y), (r22_x, r22_y), color=(0, 255, 0), thickness=5)

        r31_x = 1290
        r31_y = 229
        r32_x = 1692
        r32_y = 631
        cv2.rectangle(jpg, (r31_x, r31_y), (r32_x, r32_y), color=(0, 255, 0), thickness=5)

        r41_x = 508
        r41_y = 240
        r42_x = 884
        r42_y = 616
        cv2.rectangle(jpg, (r41_x, r41_y), (r42_x, r42_y), color=(0, 255, 0), thickness=5)

        r51_x = 1545
        r51_y = 0
        r52_x = 1891
        r52_y = 302
        cv2.rectangle(jpg, (r51_x, r51_y), (r52_x, r52_y), color=(0, 255, 0), thickness=5)

        r61_x = 758
        r61_y = 0
        r62_x = 1092
        r62_y = 331
        cv2.rectangle(jpg, (r61_x, r61_y), (r62_x, r62_y), color=(0, 255, 0), thickness=5)
        # y1_line = 350
        # y2_line = 700
        # x_line = 1050
        # cv2.line(jpg, (0, y1_line), (1919, y1_line), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (0, y2_line), (1919, y2_line), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (x_line, 0), (x_line, 1079), (0, 0, 255), thickness=5)
        # plt.hlines(y1_line, 0, 1919, colors='r')
        # plt.hlines(y2_line, 0, 1919, colors='r')
        # plt.vlines(x_line, 0, 1079, colors='r')
    elif point == 5:

        r11_x = 724
        r11_y = 361
        r12_x = 1078
        r12_y = 715
        cv2.rectangle(jpg, (r11_x, r11_y), (r12_x, r12_y), color=(0, 255, 0), thickness=5)
        #
        r21_x = 343
        r21_y = 291
        r22_x = 670
        r22_y = 618
        cv2.rectangle(jpg, (r21_x, r21_y), (r22_x, r22_y), color=(0, 255, 0), thickness=5)
        #
        r31_x = 91
        r31_y = 229
        r32_x = 382
        r32_y = 520
        cv2.rectangle(jpg, (r31_x, r31_y), (r32_x, r32_y), color=(0, 255, 0), thickness=5)
        #
        r41_x = 1172
        r41_y = 154
        r42_x = 1484
        r42_y = 466
        cv2.rectangle(jpg, (r41_x, r41_y), (r42_x, r42_y), color=(0, 255, 0), thickness=5)
        #
        r51_x = 823
        r51_y = 111
        r52_x = 1105
        r52_y = 393
        cv2.rectangle(jpg, (r51_x, r51_y), (r52_x, r52_y), color=(0, 255, 0), thickness=5)
        #
        r61_x = 529
        r61_y = 68
        r62_x = 784
        r62_y = 323
        cv2.rectangle(jpg, (r61_x, r61_y), (r62_x, r62_y), color=(0, 255, 0), thickness=5)
        #

        # point11_x = 7
        # point11_y = 104
        # point12_x = 1919
        # point12_y = 620
        #
        # point21_x = 400
        # point21_y = 20
        # point22_x = 1919
        # point22_y = 375
        #
        # point31_x = 11
        # point31_y = 740
        # point32_x = 1680
        # point32_y = 0
        #
        # point41_x = 0
        # point41_y = 1068
        # point42_x = 1919
        # point42_y = 162
        #
        # cv2.line(jpg, (point11_x, point11_y), (point12_x, point12_y), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (point21_x, point21_y), (point22_x, point22_y), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (point31_x, point31_y), (point32_x, point32_y), (0, 0, 255), thickness=5)
        # cv2.line(jpg, (point41_x, point41_y), (point42_x, point42_y), (0, 0, 255), thickness=5)
    elif point == 6:
        r11_x = 1042
        r11_y = 736
        r12_x = 1254
        r12_y = 948
        cv2.rectangle(jpg, (r11_x, r11_y), (r12_x, r12_y), color=(0, 255, 0), thickness=5)

        r21_x = 550
        r21_y = 733
        r22_x = 748
        r22_y = 931
        cv2.rectangle(jpg, (r21_x, r21_y), (r22_x, r22_y), color=(0, 255, 0), thickness=5)

        r31_x = 187
        r31_y = 729
        r32_x = 385
        r32_y = 927
        cv2.rectangle(jpg, (r31_x, r31_y), (r32_x, r32_y), color=(0, 255, 0), thickness=5)

        r41_x = 1282
        r41_y = 627
        r42_x = 1508
        r42_y = 853
        cv2.rectangle(jpg, (r41_x, r41_y), (r42_x, r42_y), color=(0, 255, 0), thickness=5)

        r51_x = 933
        r51_y = 573
        r52_x = 1109
        r52_y = 749
        cv2.rectangle(jpg, (r51_x, r51_y), (r52_x, r52_y), color=(0, 255, 0), thickness=5)

        r61_x = 515
        r61_y = 596
        r62_x = 685
        r62_y = 766
        cv2.rectangle(jpg, (r61_x, r61_y), (r62_x, r62_y), color=(0, 255, 0), thickness=5)

        r71_x = 1485
        r71_y = 490
        r72_x = 1651
        r72_y = 656
        cv2.rectangle(jpg, (r71_x, r71_y), (r72_x, r72_y), color=(0, 255, 0), thickness=5)

        r81_x = 1100
        r81_y = 500
        r82_x = 1260
        r82_y = 660
        cv2.rectangle(jpg, (r81_x, r81_y), (r82_x, r82_y), color=(0, 255, 0), thickness=5)

        r91_x = 806
        r91_y = 484
        r92_x = 962
        r92_y = 640
        cv2.rectangle(jpg, (r91_x, r91_y), (r92_x, r92_y), color=(0, 255, 0), thickness=5)

        r101_x = 1656
        r101_y = 396
        r102_x = 1810
        r102_y = 550
        cv2.rectangle(jpg, (r101_x, r101_y), (r102_x, r102_y), color=(0, 255, 0), thickness=5)

        r111_x = 1359
        r111_y = 393
        r112_x = 1501
        r112_y = 535
        cv2.rectangle(jpg, (r111_x, r111_y), (r112_x, r112_y), color=(0, 255, 0), thickness=5)

        r121_x = 984
        r121_y = 418
        r122_x = 1126
        r122_y = 560
        cv2.rectangle(jpg, (r121_x, r121_y), (r122_x, r122_y), color=(0, 255, 0), thickness=5)

    for index, face in enumerate(json):
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


def rollcall(json, search_result, point):
    inf_set = dict()
    # if point == 1:
    #     y_line = 421
    #     x_line = 950
    # elif point == 2:
    #     y_line = 471
    #     x_line = 950
    # elif point == 3:
    #     y1_line = 350
    #     y2_line = 700
    #     x_line = 950

    for index, face in enumerate(json):
        rectangle = face['face_rectangle']
        center_x = rectangle['left'] + rectangle['width'] / 2
        center_y = rectangle['top'] + rectangle['height'] / 2
        if point == 1:
            r11_x = 0
            r11_y = 344
            r12_x = 613
            r12_y = 1013
            if judge_in_out(center_x, center_y, r11_x, r11_y, r12_x, r12_y):
                inf_set.update({'1': search_result[index]['face_token']})
                break

            r21_x = 759
            r21_y = 403
            r22_x = 1431
            r22_y = 1075
            if judge_in_out(center_x, center_y, r21_x, r21_y, r22_x, r22_y):
                inf_set.update({'2': search_result[index]['face_token']})
                break

            r31_x = 1072
            r31_y = 0
            r32_x = 1630
            r32_y = 471
            if judge_in_out(center_x, center_y, r31_x, r31_y, r32_x, r32_y):
                inf_set.update({'3': search_result[index]['face_token']})
                break

            r41_x = 323
            r41_y = 0
            r42_x = 869
            r42_y = 437
            if judge_in_out(center_x, center_y, r41_x, r41_y, r42_x, r42_y):
                inf_set.update({'4': search_result[index]['face_token']})
                break  #
            # if center_y > y_line:
            #     if center_x < x_line:
            #         # 1号座位
            #         inf_set.update({'1': json['results'][index]['face_token']})
            #     else:
            #         # 2号座位
            #         inf_set.update({'2': json['results'][index]['face_token']})
            # else:
            #     if center_x < x_line:
            #         # 3号座位
            #         inf_set.update({'3': json['results'][index]['face_token']})
            #     else:
            #         # 4号座位
            #         inf_set.update({'4': json['results'][index]['face_token']})
        elif point == 2:
            r11_x = 328
            r11_y = 456
            r12_x = 1012
            r12_y = 1080
            if judge_in_out(center_x, center_y, r11_x, r11_y, r12_x, r12_y):
                inf_set.update({'5': search_result[index]['face_token']})
                break

            r21_x = 1288
            r21_y = 349
            r22_x = 1920
            r22_y = 1042
            if judge_in_out(center_x, center_y, r21_x, r21_y, r22_x, r22_y):
                inf_set.update({'6': search_result[index]['face_token']})
                break

            r31_x = 1127
            r31_y = 0
            r32_x = 1679
            r32_y = 457
            if judge_in_out(center_x, center_y, r31_x, r31_y, r32_x, r32_y):
                inf_set.update({'7': search_result[index]['face_token']})
                break

            r41_x = 263
            r41_y = 0
            r42_x = 833
            r42_y = 565
            if judge_in_out(center_x, center_y, r41_x, r41_y, r42_x, r42_y):
                inf_set.update({'8': search_result[index]['face_token']})
                break  #
            # if center_y > y_line:
            #     if center_x < x_line:
            #         # 5号座位
            #         inf_set.update({'5': json['results'][index]['face_token']})
            #     else:
            #         # 6号座位
            #         inf_set.update({'6': json['results'][index]['face_token']})
            # else:
            #     if center_x < x_line:
            #         # 7号座位
            #         inf_set.update({'7': json['results'][index]['face_token']})
            #     else:
            #         # 8号座位
            #         inf_set.update({'8': json['results'][index]['face_token']})
        elif point == 3:
            r11_x = 1211
            r11_y = 574
            r12_x = 1681
            r12_y = 1044
            if judge_in_out(center_x, center_y, r11_x, r11_y, r12_x, r12_y):
                inf_set.update({'9': search_result[index]['face_token']})
                break

            r21_x = 216
            r21_y = 647
            r22_x = 692
            r22_y = 1080
            if judge_in_out(center_x, center_y, r21_x, r21_y, r22_x, r22_y):
                inf_set.update({'10': search_result[index]['face_token']})
                break

            r31_x = 1185
            r31_y = 224
            r32_x = 1583
            r32_y = 622
            if judge_in_out(center_x, center_y, r31_x, r31_y, r32_x, r32_y):
                inf_set.update({'11': search_result[index]['face_token']})
                break

            r41_x = 385
            r41_y = 302
            r42_x = 787
            r42_y = 704
            if judge_in_out(center_x, center_y, r41_x, r41_y, r42_x, r42_y):
                inf_set.update({'12': search_result[index]['face_token']})
                break  #

            r51_x = 1141
            r51_y = 0
            r52_x = 1489
            r52_y = 330
            if judge_in_out(center_x, center_y, r51_x, r51_y, r52_x, r52_y):
                inf_set.update({'13': search_result[index]['face_token']})
                break  #

            r61_x = 419
            r61_y = 13
            r62_x = 761
            r62_y = 355
            if judge_in_out(center_x, center_y, r61_x, r61_y, r62_x, r62_y):
                inf_set.update({'14': search_result[index]['face_token']})
                break
            # if center_y < y1_line:
            #     if center_x < x_line:
            #         # 9号座位
            #         inf_set.update({'9': json['results'][index]['face_token']})
            #     else:
            #         # 10号座位
            #         inf_set.update({'10': json['results'][index]['face_token']})
            # elif center_y < y2_line:
            #     if center_x < x_line:
            #         # 11号座位
            #         inf_set.update({'11': json['results'][index]['face_token']})
            #     else:
            #         # 12号座位
            #         inf_set.update({'12': json['results'][index]['face_token']})
            # else:
            #     if center_x < x_line:
            #         # 13号座位
            #         inf_set.update({'13': json['results'][index]['face_token']})
            #     else:
            #         # 14号座位
            #         inf_set.update({'14': json['results'][index]['face_token']})
        elif point == 4:
            r11_x = 1135
            r11_y = 599
            r12_x = 1599
            r12_y = 1063
            if judge_in_out(center_x, center_y, r11_x, r11_y, r12_x, r12_y):
                inf_set.update({'15': search_result[index]['face_token']})
                break

            r21_x = 0
            r21_y = 624
            r22_x = 427
            r22_y = 1068
            if judge_in_out(center_x, center_y, r21_x, r21_y, r22_x, r22_y):
                inf_set.update({'16': search_result[index]['face_token']})
                break

            r31_x = 1290
            r31_y = 229
            r32_x = 1692
            r32_y = 631
            if judge_in_out(center_x, center_y, r31_x, r31_y, r32_x, r32_y):
                inf_set.update({'17': search_result[index]['face_token']})
                break

            r41_x = 508
            r41_y = 240
            r42_x = 884
            r42_y = 616
            if judge_in_out(center_x, center_y, r41_x, r41_y, r42_x, r42_y):
                inf_set.update({'18': search_result[index]['face_token']})
                break  #

            r51_x = 1545
            r51_y = 0
            r52_x = 1891
            r52_y = 302
            if judge_in_out(center_x, center_y, r51_x, r51_y, r52_x, r52_y):
                inf_set.update({'19': search_result[index]['face_token']})
                break  #

            r61_x = 758
            r61_y = 0
            r62_x = 1092
            r62_y = 331
            if judge_in_out(center_x, center_y, r61_x, r61_y, r62_x, r62_y):
                inf_set.update({'20': search_result[index]['face_token']})
                break
            # if center_y < y1_line:
            #     if center_x < x_line:
            #         # 15号座位
            #         inf_set.update({'15': json['results'][index]['face_token']})
            #     else:
            #         # 16号座位
            #         inf_set.update({'16': json['results'][index]['face_token']})
            # elif center_y < y2_line:
            #     if center_x < x_line:
            #         # 17号座位
            #         inf_set.update({'17': json['results'][index]['face_token']})
            #     else:
            #         # 18号座位
            #         inf_set.update({'18': json['results'][index]['face_token']})
            # else:
            #     if center_x < x_line:
            #         # 19号座位
            #         inf_set.update({'19': json['results'][index]['face_token']})
            #     else:
            #         # 20号座位
            #         inf_set.update({'20': json['results'][index]['face_token']})
        elif point == 5:

            r11_x = 724
            r11_y = 361
            r12_x = 1078
            r12_y = 715
            if judge_in_out(center_x, center_y, r11_x, r11_y, r12_x, r12_y):
                inf_set.update({'21': search_result[index]['face_token']})
                break
            r21_x = 343
            r21_y = 291
            r22_x = 670
            r22_y = 618
            if judge_in_out(center_x, center_y, r21_x, r21_y, r22_x, r22_y):
                inf_set.update({'22': search_result[index]['face_token']})
                break

            r31_x = 91
            r31_y = 229
            r32_x = 382
            r32_y = 520
            if judge_in_out(center_x, center_y, r31_x, r31_y, r32_x, r32_y):
                inf_set.update({'23': search_result[index]['face_token']})
                break
            #
            r41_x = 1172
            r41_y = 154
            r42_x = 1484
            r42_y = 466
            if judge_in_out(center_x, center_y, r41_x, r41_y, r42_x, r42_y):
                inf_set.update({'24': search_result[index]['face_token']})
                break  #
            r51_x = 823
            r51_y = 111
            r52_x = 1105
            r52_y = 393
            if judge_in_out(center_x, center_y, r51_x, r51_y, r52_x, r52_y):
                inf_set.update({'25': search_result[index]['face_token']})
                break  #
            r61_x = 529
            r61_y = 68
            r62_x = 784
            r62_y = 323
            if judge_in_out(center_x, center_y, r61_x, r61_y, r62_x, r62_y):
                inf_set.update({'26': search_result[index]['face_token']})
                break
        elif point == 6:
            r11_x = 1042
            r11_y = 736
            r12_x = 1254
            r12_y = 948
            if judge_in_out(center_x, center_y, r11_x, r11_y, r12_x, r12_y):
                inf_set.update({'27': search_result[index]['face_token']})
                break
            r21_x = 550
            r21_y = 733
            r22_x = 748
            r22_y = 931
            if judge_in_out(center_x, center_y, r21_x, r21_y, r22_x, r22_y):
                inf_set.update({'28': search_result[index]['face_token']})
                break
            r31_x = 187
            r31_y = 729
            r32_x = 385
            r32_y = 927
            if judge_in_out(center_x, center_y, r31_x, r31_y, r32_x, r32_y):
                inf_set.update({'29': search_result[index]['face_token']})
                break
            r41_x = 1282
            r41_y = 627
            r42_x = 1508
            r42_y = 853
            if judge_in_out(center_x, center_y, r41_x, r41_y, r42_x, r42_y):
                inf_set.update({'30': search_result[index]['face_token']})
                break  #
            r51_x = 933
            r51_y = 573
            r52_x = 1109
            r52_y = 749
            if judge_in_out(center_x, center_y, r51_x, r51_y, r52_x, r52_y):
                inf_set.update({'31': search_result[index]['face_token']})
                break  #
            r61_x = 515
            r61_y = 596
            r62_x = 685
            r62_y = 766
            if judge_in_out(center_x, center_y, r61_x, r61_y, r62_x, r62_y):
                inf_set.update({'32': search_result[index]['face_token']})
                break
            r71_x = 1485
            r71_y = 490
            r72_x = 1651
            r72_y = 656
            if judge_in_out(center_x, center_y, r71_x, r71_y, r72_x, r72_y):
                inf_set.update({'33': search_result[index]['face_token']})
                break
            r81_x = 1100
            r81_y = 500
            r82_x = 1260
            r82_y = 660
            if judge_in_out(center_x, center_y, r81_x, r81_y, r82_x, r82_y):
                inf_set.update({'34': search_result[index]['face_token']})
                break
            r91_x = 806
            r91_y = 484
            r92_x = 962
            r92_y = 640
            if judge_in_out(center_x, center_y, r91_x, r91_y, r92_x, r92_y):
                inf_set.update({'35': search_result[index]['face_token']})
                break
            r101_x = 1656
            r101_y = 396
            r102_x = 1810
            r102_y = 550
            if judge_in_out(center_x, center_y, r101_x, r101_y, r102_x, r102_y):
                inf_set.update({'36': search_result[index]['face_token']})
                break
            r111_x = 1359
            r111_y = 393
            r112_x = 1501
            r112_y = 535
            if judge_in_out(center_x, center_y, r111_x, r111_y, r112_x, r112_y):
                inf_set.update({'37': search_result[index]['face_token']})
                break
            r121_x = 984
            r121_y = 418
            r122_x = 1126
            r122_y = 560
            if judge_in_out(center_x, center_y, r121_x, r121_y, r122_x, r122_y):
                inf_set.update({'38': search_result[index]['face_token']})
                break
    return inf_set


def print_box(json, num):
    for index, face in enumerate(json['faces']):
        rectangle = face['face_rectangle']
        left = rectangle['left'] - 0.5 * rectangle['width']
        top = rectangle['top'] - 0.5 * rectangle['height']
        right = rectangle['left'] + 1.5 * rectangle['width']
        down = rectangle['top'] + 1.5 * rectangle['height']
        if left < 0:
            left = 0
        if top < 0:
            top = 0
        if right > 1920:
            right = 1920
        if down > 1080:
            down = 1080

        print(
            'r{}1_x = {}\r\nr{}1_y = {}\r\nr{}2_x = {}\r\nr{}2_y = {}\r\ncv2.rectangle(jpg, (r{}1_x, r{}1_y), (r{}2_x, r{}2_y), color=(0, 255, 0), thickness=5)'.format(
                num,
                int(left),
                num, int(top),
                num,
                int(right),
                num,
                int(down),
                num, num,
                num,
                num, ))


def judge_in_out(center_x, center_y, Left, Top, Right, Down):
    if center_x > Left and center_x < Right and center_y > Top and center_y < Down:
        return True
    else:
        return False


if __name__ == '__main__':
    # pitch_angle越大，低头越严重，大于10就认为是低头
    # facequality越大那么脸越清晰，越能证明抬头（不太准）
    # vector_z_component越大越认真，大于0.9就认为是向上
    # json = url_detect('../img/t3.jpg')
    # face_rectangle1 = {"width": 181, "top": 155, "left": 94, "height": 181}
    # face_rectangle2 = {"width": 121, "top": 205, "left": 449, "height": 121}
    # url_compare('../img/t1.jpg', '../img/t4.jpg', face_rectangle1, face_rectangle2)

    # url_faceset_create(outer_id='faceset_test')
    # json = url_faceset_getfacesets()
    # json = url_faceset_getdetail(outer_id='faceset_test')
    # url_faceset_add(outer_id='faceset_test',
    #                 face_tokens='32f4b716dccb632139d33e3b0fbe99a9,2476e3a308dafd3ac987cc237836e9b7')  # 佟丽娅、吴京的face_token
    # json = url_search(face_token='770dd86936eb7f0335305a4c5a7985d6', filepath=None, outer_id='faceset_test')

    # infor = None
    path = '../img/point5/1552719282.jpg'
    search_result, faces = url_search_all(path, outer_id='faceset_classmate')
    show_jpg(path, faces, point=5)
    infor = rollcall(faces, search_result, point=5)
    # print_box(json, 12)
    exit()
