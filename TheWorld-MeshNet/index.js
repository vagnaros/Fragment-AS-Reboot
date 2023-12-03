const http = require('http')
const port = 3000

const server = http.createServer(function(req, res){
    res.write('Hello Node')
    res.end()
})

server.listen(port, function(error){
    if (error){
        console.log('Something Went Wrong... ', error)
    } else {
        console.log('Server is Listening on port: ' + port)
    }
})