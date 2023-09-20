let userid = localStorage.getItem("userid");
let token = localStorage.getItem("token");

let loginButton=document.getElementById('login-button');
let registerButton=document.getElementById('register-button');
let loginView=document.getElementById('login');
let register=document.getElementById('register');
let form_box=document.getElementsByClassName('form-box')[0];
let register_box=document.getElementsByClassName('register-box')[0];
let login_box=document.getElementsByClassName('login-box')[0];

let registerUserId = document.getElementById('register-user-id');
let registerUserName = document.getElementById('register-user-name');
let registerPassword = document.getElementById('register-password');
let registerPasswordConfirm = document.getElementById('register-password-confirm');

let registerUserIdMessage = document.getElementById('register-user-id-message');
let registerUserNameMessage = document.getElementById('register-user-name-message');
let registerPasswordMessage = document.getElementById('register-password-message');
let registerPasswordConfirmMessage = document.getElementById('register-password-confirm-message');

let loginUserId = document.getElementById('login-user-id');
let loginPassword = document.getElementById('login-password');

let loginUserIdMessage = document.getElementById("login-user-id-message");
let loginPasswordMessage = document.getElementById('login-password-message');

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

function isStrRight(str) {
    var regex = /[^A-Za-z0-9_]/;
    return regex.test(str);
}

function isNumber(str) {
    var regex = /[^0-9]/;
    return regex.test(str);
}

function isNameStr(str) {
    var regex = /[^\p{Script=Han}a-zA-Z0-9]/u;
    return regex.test(str);
}

register.addEventListener('click',()=>{
    form_box.style.transform='translateX(80%)';
    login_box.classList.add('hidden');
    register_box.classList.remove('hidden');

    registerUserIdMessage.textContent = "";
    registerUserNameMessage.textContent = "";
    registerPasswordMessage.textContent = "";
    registerPasswordConfirmMessage.textContent = "";
});

loginView.addEventListener('click',()=>{
    form_box.style.transform='translateX(0%)';
    register_box.classList.add('hidden');
    login_box.classList.remove('hidden');

    loginUserIdMessage.textContent = "";
    loginPasswordMessage.textContent = "";
});

registerButton.addEventListener('click',()=>{
    let registerFlag = true;

    if(!checkNotNull(registerUserId.value)) {
        registerUserIdMessage.textContent = "请输入用户ID";
        registerFlag &&= false;
    } else if(isNumber(registerUserId.value)) {
        showError("用户Id只能为 数字、字母、下划线");
        registerFlag &&= false;
    } else {
        registerUserIdMessage.textContent = "";
        registerFlag &&= true;
    }

    if(!checkNotNull(registerUserName.value)) {
        registerUserNameMessage.textContent = "请输入用户名";
        registerFlag &&= false;
    } else if(isNameStr(registerUserName.value)) {
        showError("用户名只能为 中文、字母、数字、下划线");
        registerFlag &&= false;
    } else {
        registerUserNameMessage.textContent = "";
        registerFlag &&= true;
    }

    if(!checkNotNull(registerPassword.value)) {
        registerPasswordMessage.textContent = "请输入密码";
        registerFlag &&= false;
    } else if(registerPassword.value.length < 6) {
        showError("密码长度必须大于6");
        registerFlag &&= false;
    } else if(isStrRight(registerPassword.value)) {
        showError("密码只能为 数字、字母、下划线");
        registerFlag &&= false;
    } else {
        registerPasswordMessage.textContent = "";
        registerFlag &&= true;
    }

    if(!checkNotNull(registerPasswordConfirm.value)) {
        registerPasswordConfirmMessage.textContent = "请再次输入密码";
        registerFlag &&= false;
    } else {
        registerPasswordConfirmMessage.textContent = "";
        registerFlag &&= true;
    }

    if(registerPassword.value !== registerPasswordConfirm.value) {
        showError("两次输入密码不一致");
        registerFlag &&= false;
    }

    if(registerFlag) {
        axios.post('http://localhost:9999/register', {
            userid: registerUserId.value,
            username: registerUserName.value,
            password: registerPassword.value
        }).then(function (response) {
            let code = response.data.code
            switch (code) {
                case 50010: {
                    showError("服务器异常");
                    break;
                }
                case 50020: {
                    showError("请稍候再试");
                    break;
                }
                case 20063: {
                    showError("用户ID已经被注册");
                    break;
                }
                case 20062: {
                    showError("账号和密码不能为空");
                    break;
                }
                case 20061: {
                    showInfo("注册成功");

                    form_box.style.transform='translateX(0%)';
                    register_box.classList.add('hidden');
                    login_box.classList.remove('hidden');

                    let loginUserId = document.getElementById('login-user-id');
                    loginUserId.value = response.data.data.userid;
                    break;
                }
            }
        }).catch(function (error) {
            console.log(error);
        });
    }
});

loginButton.addEventListener('click',()=>{
    let loginFlag = true;

    if(!checkNotNull(loginUserId.value)) {
        loginUserIdMessage.textContent = "请输入用户ID";
        loginFlag &&= false;
    } else if(isNumber(loginUserId.value)) {
        showError("用户Id只能为 数字、字母、下划线");
        loginFlag &&= false;
    } else {
        loginUserIdMessage.textContent = "";
        loginFlag &&= true;
    }

    if(!checkNotNull(loginPassword.value)) {
        loginPasswordMessage.textContent = "请输入密码";
        loginFlag &&= false;
    } else if(isStrRight(loginPassword.value)) {
        showError("密码只能为 数字、字母、下划线");
        loginFlag &&= false;
    } else {
        loginPasswordMessage.textContent = "";
        loginFlag &&= true;
    }

    if(loginFlag) {
        axios.post('http://localhost:9999/login', {
            userid: loginUserId.value,
            username: "",
            password: loginPassword.value
        }).then(function (response) {
            let code = response.data.code
            switch (code) {
                case 50010: {
                    showError("服务器异常");
                    break;
                }
                case 50020: {
                    showError("请稍候再试");
                    break;
                }
                case 20053: {
                    showError("账号或密码不正确");
                    break;
                }
                case 20052: {
                    showError("账号和密码不能为空");
                    break;
                }
                case 20051: {
                    localStorage.removeItem('userid');
                    localStorage.removeItem('username');
                    localStorage.removeItem('token');
                    localStorage.setItem('userid', response.data.data.userid);
                    localStorage.setItem('username', response.data.data.username);
                    localStorage.setItem('token', response.data.data.token);
                    self.location = "http://localhost:9999/html/rooms.html";
                    break;
                }
            }
        }).catch(function (error) {
            console.log(error);
        });
    }
});

registerUserId.oninput = function() {
    registerUserIdMessage.textContent = "";
}

registerUserName.oninput = function() {
    registerUserNameMessage.textContent = "";
}

registerPassword.oninput = function() {
    registerPasswordMessage.textContent = "";
}

registerPasswordConfirm.oninput = function() {
    registerPasswordConfirmMessage.textContent = "";
}

loginUserIdMessage.oninput = function() {
    loginUserIdMessage.textContent = "";
}

loginPasswordMessage.oninput = function() {
    loginPasswordMessage.textContent = "";
}

function checkNotNull(str) {
    return !(str == null || str === "" || str.length === 0);
}

