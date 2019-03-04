# -*- coding: utf-8 -*-
import urllib.request
import urllib.error
import time
import json


def url_detect(filepath):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/detect'
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    filepath = "../img/" + filepath
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
    # data.append('--%s' % boundary)
    # data.append('Content-Disposition: form-data; name="%s"\r\n' % 'return_attributes')
    # data.append(
    #     "gender,age,smiling,headpose,facequality,blur,eyestatus,emotion,ethnicity,beauty,mouthstatus,eyegaze,skinstatus")
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


def url_compare(filepath1, filepath2, face_token1=None, face_token2=None):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/compare'
    # 免费
    # key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    # secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'

    filepath1 = "../img/" + filepath1
    filepath2 = "../img/" + filepath2
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    if face_token1 != None:
        data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_token1')
        data.append(face_token1)
        data.append('--%s' % boundary)
        data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_token2')
        data.append(face_token1)
        data.append('--%s' % boundary)
    else:
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


if __name__ == '__main__':
    # {"image_id": "9cfaRGDXY/39z7rqFiccMw==", "request_id": "1551685651,88575546-b3ac-4c1d-bb5a-cfc1c8160b2e", "time_used": 1362, "faces": [{"face_rectangle": {"width": 158, "top": 1616, "left": 1776, "height": 158}, "face_token": "792d9783dc6889ba53b9006c4386fbc0"}]}
    # url_detect('t4.jpg')
    # t1 c35a0e984f8ddb7e8042de975ef495f9
    # t2 1c038cb000067e5fa8eaa1e8209ff597
    # ?2 53e4431701bfab9bb49c746669724c17
    url_compare('t1.jpg', 't2.jpg', 'c35a0e984f8ddb7e8042de975ef495f9', 'c35a0e984f8ddb7e8042de975ef495f9')
    exit()
