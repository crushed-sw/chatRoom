let userid = localStorage.getItem("userid");
if(userid == null || userid === "") {
    localStorage.removeItem("token");
    self.location = "http://localhost:9999/html/login.html";
}

let token = localStorage.getItem("token");
if(token == null || token === "") {
    localStorage.removeItem("userid");
    self.location = "http://localhost:9999/html/login.html";
}

let isServerClose = true;

let rooms = document.querySelector(".rooms");
let addButton = document.querySelector(".create-room");
let logoutButton = document.querySelector(".logout");

let socket = new WebSocket("ws://localhost:9999/rooms/" + userid);

function showError(message, duration = 3000) {
    const notification = document.querySelector('.notification');
    notification.textContent = message;
    notification.classList.add('error');

    setTimeout(function() {
        notification.classList.remove('error');
    }, duration);
}

function showInfo(message, duration = 3000) {
    const notification = document.querySelector('.notification');
    notification.textContent = message;
    notification.classList.add('success');

    setTimeout(function() {
        notification.classList.remove('success');
    }, duration);
}

let isdelete = localStorage.getItem("isdelete");
localStorage.removeItem("isdelete");
if(isdelete != null && isdelete !== "") {
    showInfo("原房间已被房主删除");
}

function checkRoomName(str) {
    var regex = /[^\p{Script=Han}a-zA-Z0-9]/u;
    return regex.test(str);
}

function clearButtons() {
    let elems = document.querySelectorAll(".room");
    elems.forEach((elem) => {
        rooms.removeChild(elem);
    })
}

function addButtons(roomname, userid, roomid, username) {
    console.log(roomname, userid, roomid, username);
    let button = document.createElement("button");
    button.className = "room";
    button.innerHTML = "<div class='name'>" + roomname + "</div><div>" + "房主:" + username + "</div>"
    button.addEventListener('click', function(){
        localStorage.removeItem('roomid');
        localStorage.removeItem('roomname');
        localStorage.removeItem('roomownerid');
        localStorage.removeItem('roomownername');
        localStorage.setItem('roomid', roomid);
        localStorage.setItem('roomname', roomname);
        localStorage.setItem('roomownerid', userid);
        localStorage.setItem('roomownername', username);
        isServerClose = false;
        self.location = "http://localhost:9999/html/chat.html";
    });

    rooms.appendChild(button);
}

socket.onmessage = function(e) {
    console.log(e);
    let jsonData = JSON.parse(e.data);
    if(jsonData.code == 20041) {
        clearButtons();
        let elems = jsonData.data;
        elems.forEach((elem) => {
            addButtons(elem.roomname, elem.roomuser, elem.roomid, elem.username);
        });
    } else if(jsonData.code == 20072) {
        localStorage.removeItem('token');
        localStorage.removeItem("userid");
        localStorage.removeItem('roomid');
        localStorage.removeItem("username");
        localStorage.removeItem('roomname');
        localStorage.removeItem('roomownerid');
        localStorage.removeItem('roomownername');
        self.location = "http://localhost:9999/html/login.html";
    }
}

socket.onclose = function() {
    if(isServerClose == true) {
        localStorage.removeItem('token');
        localStorage.removeItem("userid");
        localStorage.removeItem('roomid');
        localStorage.removeItem("username");
        localStorage.removeItem('roomname');
        localStorage.removeItem('roomownerid');
        localStorage.removeItem('roomownername');
        self.location = "http://localhost:9999/html/login.html";
    }
}

addButton.addEventListener('click', function() {
    roomname = window.prompt("请输入聊天室名称");

    if(roomname === null) {
        return;
    } else if(roomname === "") {
        showError("房间名称必须不为空");
    } else if(checkRoomName(roomname)) {
        showError("房间名称必须由汉字、数字、字母、下划线组成");
    } else {
        socket.send(JSON.stringify({
            cause: "addroom",
            userid: userid,
            roomname: roomname,
            token: token
        }));
        
    }
});

logoutButton.addEventListener('click', function() {
    socket.close();
    localStorage.removeItem('userid');
    self.location = "http://localhost:9999/html/login.html";
});

window.onbeforeunload = function() {
    socket.close()
}
