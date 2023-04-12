using Sockets, HTTP, Dates


const PORT = 9081

function getInRoot(req::HTTP.Request)
    # request body 수집
    println(req)

    # response body 작성
    now = Dates.format(Dates.now(), "yyyy-mm-dd HH:MM:SS.s")
    response = "$now\n"

    println(response)

    return HTTP.Response(200, response)
end

# define REST endpoints to dispatch to "service" functions
const ROUTER = HTTP.Router()
HTTP.register!(ROUTER, "GET", "/", getInRoot)
server = HTTP.serve!(ROUTER, "0.0.0.0", PORT)
println("Julia version: ", VERSION)
println("Server started")
wait(server)

# close the server which will stop the HTTP server from listening
# close(server)
# @assert istaskdone(server.task)