package main

import (
	"fmt"
	"net/http"
	"runtime"
	"strconv"
	"time"
)

const PORT = 9081

func handler(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path != "/" {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprint(w, "Not Found")
		return
	}

	if r.Method != "GET" {
		w.WriteHeader(http.StatusMethodNotAllowed)
		fmt.Fprint(w, "Method Not Allowed")
		return
	}

	// request headers 출력
	for name, values := range r.Header {
		for _, value := range values {
			fmt.Printf("%s: %s\n", name, value)
		}
	}

	// request body 수집
	length, _ := strconv.Atoi(r.Header.Get("Content-Length"))
	body := make([]byte, length)
	r.Body.Read(body)
	fmt.Printf("%s\n", body)

	// response body 작성
	now := time.Now().Format("2006-01-02 15:04:05")
	response := fmt.Sprintf("%s.%03d\n", now, time.Now().UnixNano()/1e6%1000)
	fmt.Printf("%s", response)
	fmt.Fprint(w, response)
}

func main() {
	fmt.Printf("Go version : %s\n", runtime.Version())
	fmt.Printf("Server started\n")
	http.HandleFunc("/", handler)
	http.ListenAndServe(fmt.Sprintf(":%d", PORT), nil)
}
