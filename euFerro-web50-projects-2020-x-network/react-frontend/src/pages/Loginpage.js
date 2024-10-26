import "./Login&Register.css";
import "./Loading.css";
import { useEffect, useState } from 'react';
import { Link, redirect, useNavigate } from "react-router-dom";
import TooglePassword from "../components/TooglePassword";

function Loginpage() {

    const [is_loading, setLoading] = useState(false);

    function clearMsgs() {
        const msgDivs = document.querySelectorAll('.msg-div');
        msgDivs.forEach(div => {
            div.childNodes.forEach(child => {
                child.remove();
            });
        })
    }

    function login(event) {
        event.preventDefault();

        // Clear notice msgs
        clearMsgs();

        const usernameInput = document.querySelector('#login-username-input');
        const passwordInput = document.querySelector('#login-pass-input');

        if (usernameInput.value === '') {
            usernameInput.style.borderBottom = '4px solid #ddaa00';
            const usernameMsg = document.querySelector('#username-msg');
            usernameMsg.innerHTML = 'fill here your username';
            usernameMsg.style.color = '#ddaa00';
        }
        if (passwordInput.value === '') {
            passwordInput.style.borderBottom = '4px solid #ddaa00';
            const passwordMsg = document.querySelector('#password-msg');
            passwordMsg.innerHTML = 'fill here your password';
            passwordMsg.style.color = '#ddaa00';
        }
        if (usernameInput.value === '' || passwordInput.value === '') {
            return false
        }

        const formData = new FormData();
        formData.append('username', usernameInput.value);
        formData.append('password', passwordInput.value);

        setLoading(true);
        fetch('/login', {
            "method": "POST",
            "body": formData
        })
        .then(response => response.json())
        .then(response => {
            if (response.error) {
                // alert(response.error);

                const usernameInput = document.querySelector('#login-username-input');
                const passwordInput = document.querySelector('#login-pass-input');
                const login_form_msg = document.querySelector('#login-form-msg');

                usernameInput.style.borderBottom = '4px solid #f00';
                passwordInput.style.borderBottom = '4px solid #f00';
                login_form_msg.innerHTML = response.error;
                login_form_msg.style.color = '#f00';

            }
            if (response.user) {
                localStorage.setItem("logged_user", response.user);
                // Redirect logged user
                window.location.replace('/home');
            }
            setLoading(false);
        })

        return false
    }

    function resetLooks() {
        clearMsgs();
        const usernameInput = document.querySelector('#login-username-input');
        const passwordInput = document.querySelector('#login-pass-input');
        const login_form_msg = document.querySelector('#login-form-msg');

        usernameInput.style.borderBottom = '';
        passwordInput.style.borderBottom = '';
        login_form_msg.style = '';
    }

    useEffect(() => {
        document.title = 'Login - Social Network';
    })

    return(
        <>
        <div className="center-group-container mt-5p">
        <h2>Login</h2>

            {is_loading ? (
                <div className="lds-ring"><div></div><div></div><div></div><div></div></div>
            ) : (
                <></>
            )}

            <form onSubmit={login} className="center-group-container">
                <div id="login-form-msg" className="msg-div"></div>
                <div className="form-group center-group-container">
                    <input onChange={resetLooks} id="login-username-input" autoFocus className="text-input-2" type="text" name="username" placeholder="Username"/>
                    <div id="username-msg" className="msg-div"></div>
                </div>
                <div className="form-group center-group-container">
                    <input onChange={resetLooks} id="login-pass-input" className="text-input-2" type="password" name="password" placeholder="Password"/>
                    <TooglePassword input_selector={"#login-pass-input"}/>
                    <div id="password-msg" className="msg-div"></div>
                </div>
                <input className="primary-btn my-2" type="submit" value="Login"/>
            </form>

            Don't have an account? <Link className="teal-link" to="/register">Register here.</Link>
        </div>

        </>
    );

}

export default Loginpage;