from http.server import BaseHTTPRequestHandler, HTTPServer
import sys
import time

PORT = 9081

class RequestHandler(BaseHTTPRequestHandler):
    
    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            
            # request headers 출력
            print(self.headers)

            # request body 수집
            length = int(self.headers.get('Content-Length', 0))
            body = self.rfile.read(length).decode('utf-8')
            print(body)
            
            # response body 작성
            now = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
            response = now + '.' + f'{int(time.time() * 1000) % 1000:03d}' + '\n'
            print(response)
            self.wfile.write(response.encode('utf-8'))

        else:
            self.send_response(404)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            
            # response body 작성
            message = 'Not Found\n'
            self.wfile.write(message.encode())

# HTTP 서버 실행
with HTTPServer(("0.0.0.0", PORT), RequestHandler) as httpd:
    print("python version :", sys.version)
    print(f'Server running on port {PORT}')
    httpd.serve_forever()
