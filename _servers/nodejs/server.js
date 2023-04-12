const http = require('http');
const url = require('url');

const PORT = 9081;

const server = http.createServer(async(req, res) => {
  const reqUrl = url.parse(req.url, true);
  if (req.method === 'GET' && reqUrl.pathname === '/') {
    
    console.log(req.headers);

    // JSON 형식의 request body를 수집
    let body = '';
    for await (const chunk of req) {
      body += chunk.toString();
    }
    console.log(body);
    const now = new Date();
    const timeStr = now.toISOString().split('.')[0].replace('T', ' ') + '.' + String(now.getMilliseconds()).padStart(3, '0');
    console.log(timeStr);
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.write(timeStr + '\n');
    res.end();

  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.write('Not Found');
    res.end();
  }

  
});

server.listen(PORT, () => {
  console.log('node.js version :', process.version);
  console.log(`서버가 http://localhost:${PORT} 에서 실행 중입니다.`);
});
