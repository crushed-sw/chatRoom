let userid = localStorage.getItem("userid");
if(userid == null || userid === "") {
    localStorage.removeItem('token');
    self.location = "http://localhost:9999/html/login.html";
}

let roomid = localStorage.getItem("roomid");
if(roomid == null || roomid === "") {
    self.location = "http://localhost:9999/html/rooms.html";
}

let token = localStorage.getItem("token");
if(token == null || token === "") {
    localStorage.removeItem('userid');
    self.location = "http://localhost:9999/html/login.html";
}

let isServerClose = true;
let roomOwnerId = localStorage.getItem('roomownerid');
let roomOwnerName = localStorage.getItem('roomownername');
let roomName = localStorage.getItem('roomname');
let userName = localStorage.getItem('username');

let users = document.querySelector(".users");
let logoutRoomButton = document.querySelector(".logout-room");
let deleteRoomButton = document.querySelector(".delete-room");
let sendMessageButton = document.querySelector(".send-message");
let mainTitle = document.querySelector("#main-title");
let roomOwnerNameP = document.querySelector("#room-owner-name");
let chatMainForm = document.querySelector(".chat-main-form");
let textContent = document.querySelector(".chat-text textarea");

let socket = new WebSocket("ws://localhost:9999/chat/" + roomid + "/" + userid + "/" + userName);

mainTitle.textContent = roomName;
roomOwnerNameP.textContent = "房主:" + roomOwnerName;

if(roomOwnerId === userid) {
    deleteRoomButton.classList.add('show');
}

socket.onopen = function() {
    socket.send(JSON.stringify({
        cause: "joinroom",
        userid: userid,
        token: token
    }));
}

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

function clearUsers() {
    let elems = document.querySelectorAll(".user");
    let owner = document.querySelector(".owner");
    if(owner != null) {
        users.removeChild(owner);
    }

    elems.forEach((elem) => {
        users.removeChild(elem);
    })
}

function addUser(username) {
    let user = document.createElement("li");
    user.className = "user";
    user.innerText = username;
    users.appendChild(user);
}

function addOwner(username) {
    let user = document.createElement("li");
    user.className = "owner";
    user.innerText = username;
    users.insertAdjacentElement("afterbegin", user);
}

function addSelfMessage(name, time, message) {
    let selfMessage = document.createElement("div");
    selfMessage.className = "self message";

    let nameTime = document.createElement("div");
    nameTime.className = "name-time";
    let messageContent = document.createElement("li");
    messageContent.className = "content";
    messageContent.textContent = message;

    let messageTime = document.createElement("li");
    messageTime.className = "time";
    messageTime.textContent = time;
    let messageName = document.createElement("li");
    messageName.className = "name";
    messageName.textContent = name;

    nameTime.appendChild(messageTime);
    nameTime.appendChild(messageName);
    
    selfMessage.appendChild(messageContent);
    selfMessage.appendChild(nameTime);

    chatMainForm.appendChild(selfMessage);

    chatMainForm.scrollTop = chatMainForm.scrollHeight;
}

function addOtherMessage(name, time, message) {
    let selfMessage = document.createElement("div");
    selfMessage.className = "other message";

    let nameTime = document.createElement("div");
    nameTime.className = "name-time";
    let messageContent = document.createElement("li");
    messageContent.className = "content";
    messageContent.textContent = message;

    let messageTime = document.createElement("li");
    messageTime.className = "time";
    messageTime.textContent = time;
    let messageName = document.createElement("li");
    messageName.className = "name";
    messageName.textContent = name;

    nameTime.appendChild(messageName);
    nameTime.appendChild(messageTime);
    
    selfMessage.appendChild(nameTime);
    selfMessage.appendChild(messageContent);

    chatMainForm.appendChild(selfMessage);

    chatMainForm.scrollTop = chatMainForm.scrollHeight;
}

deleteRoomButton.addEventListener('click', function(){
    let conf = window.confirm("确定删除该房间？");
    if(conf) {
        socket.send(JSON.stringify({
            cause: "deleteroom",
            userid: userid,
            roomid: roomid,
            token: token,
        }));
    }
});

logoutRoomButton.addEventListener('click', function(){
    isServerClose = false;
    console.log("logout");
    socket.close();
    localStorage.removeItem("roomid");
    localStorage.removeItem("roomownerid")
    localStorage.removeItem("roomownername")
    self.location = "http://localhost:9999/html/rooms.html";
});

function sendMessage() {
    let textValue = textContent.value;

    if(textValue.length == 0 || textValue === "") {
        return;
    }

    let date = new Date();

    textContent.value = "";
    socket.send(JSON.stringify({
        cause: "sendmessage",
        chatid: "-1",
        roomid: roomid,
        userid: userid,
        sendtime: date.toLocaleString(),
        message: textValue,
        username: userName,
        token: token
    }));
}

sendMessageButton.addEventListener('click', function(){
    sendMessage();
});

window.addEventListener("keydown", function(e) {
    if (e.ctrlKey &&  e.key === "Enter") {
        sendMessage();
    }
}, false);

socket.onclose = function() {
    console.log("close");
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

socket.onmessage = function(e) {
    console.log(e);
    let jsonData = JSON.parse(e.data);
    if(jsonData.code == 20041) {
        clearUsers();
        let elems = jsonData.data;
        elems.forEach((elem) => {
            if(elem[0] === roomOwnerId) {
                addOwner(elem[1])
            } else {
                addUser(elem[1]);
            }
        });
    } else if(jsonData.code == 20071) {
        let jsonMessage = JSON.parse(jsonData.data);
        if(roomid == jsonMessage.roomid) {
            if(userid == jsonMessage.userid) {
                addSelfMessage(jsonMessage.username, jsonMessage.sendtime, jsonMessage.message);
            } else {
                addOtherMessage(jsonMessage.username, jsonMessage.sendtime, jsonMessage.message);
            }
        }
    } else if(jsonData.code == 20021) {
        isServerClose = false;
        console.log("20021");
        socket.close();
        localStorage.removeItem("isdelete");
        localStorage.setItem("isdelete", "true");
        self.location = "http://localhost:9999/html/rooms.html";
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

