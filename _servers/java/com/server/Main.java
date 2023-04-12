package com.server;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.Date;
import java.util.concurrent.Executors;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Main {
    private static final int PORT = 9081;

    public static void main(String[] args) throws IOException {
        System.out.println("Java version: " + System.getProperty("java.version"));

        HttpServer server = HttpServer.create(new InetSocketAddress(PORT), 0);
        server.createContext("/", new MyHandler());
        server.setExecutor(Executors.newFixedThreadPool(10));
        server.start();

        System.out.println("Server started on port " + PORT);
    }

    static class MyHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            if (!t.getRequestURI().getPath().equals("/")) {
                t.sendResponseHeaders(404, 0);
                t.getResponseBody().close();
                return;
            }

            if (!t.getRequestMethod().equals("GET")) {
                t.sendResponseHeaders(405, 0);
                t.getResponseBody().close();
                return;
            }

            // request headers 출력
            t.getRequestHeaders().forEach((k, v) -> v.forEach(value -> System.out.printf("%s: %s\n", k, value)));

            // request body 수집
            byte[] requestBody = t.getRequestBody().readAllBytes();
            System.out.println(new String(requestBody));

            // response body 작성
            String now = String.format("%tF %tT", new Date(), new Date());
            String response = now + "." + String.format("%03d", System.currentTimeMillis() % 1000) + "\n";
            System.out.print(response);
            t.sendResponseHeaders(200, response.length());
            t.getResponseBody().write(response.getBytes());
            t.getResponseBody().close();
        }
    }
}
