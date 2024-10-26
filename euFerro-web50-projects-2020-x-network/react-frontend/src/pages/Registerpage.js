import "./Login&Register.css";
import { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import TooglePassword from '../components/TooglePassword';


function Registerpage() {

    const [is_loading, setLoading] = useState(false);

    function clearMsgs() {
        const msgDivs = document.querySelectorAll('.msg-div');
        msgDivs.forEach(div => {
            div.childNodes.forEach(child => {
                child.remove();
            });
        })
    }

    function register(event) {
        event.preventDefault();

        // Clear notice msgs
        clearMsgs();

        const usernameInput = document.querySelector('#register-username-input');
        const firstNameInput = document.querySelector('#register-first-input');
        const lastNameInput = document.querySelector('#register-last-input');
        const emailInput = document.querySelector('#register-email-input');
        const passwordInput = document.querySelector('#register-pass1-input');
        const confirmationInput = document.querySelector('#register-pass2-input');
        const csrf_cookie = document.cookie.split('=');
        console.log(`Cookies csrf_token: ${csrf_cookie[1]}`);

        if (usernameInput.value === '') {
            usernameInput.style.borderBottom = '4px solid #ddaa00';
            const usernameMsg = document.querySelector('#register-username-msg');
            usernameMsg.innerHTML = 'fill here your username';
            usernameMsg.style.color = '#ddaa00';
        }
        if (firstNameInput.value === '') {
            firstNameInput.style.borderBottom = '4px solid #ddaa00';
            const firstNameMsg = document.querySelector('#register-first-msg');
            firstNameMsg.innerHTML = 'fill here your first name';
            firstNameMsg.style.color = '#ddaa00';
        }
        if (lastNameInput.value === '') {
            lastNameInput.style.borderBottom = '4px solid #ddaa00';
            const lastNameMsg = document.querySelector('#register-last-msg');
            lastNameMsg.innerHTML = 'fill here your last name';
            lastNameMsg.style.color = '#ddaa00';
        }
        if (emailInput.value === '') {
            emailInput.style.borderBottom = '4px solid #ddaa00';
            const emailMsg = document.querySelector('#register-email-msg');
            emailMsg.innerHTML = 'fill here your email';
            emailMsg.style.color = '#ddaa00';
        }
        if (passwordInput.value === '') {
            passwordInput.style.borderBottom = '4px solid #ddaa00';
            const password1Msg = document.querySelector('#register-pass1-msg');
            password1Msg.innerHTML = 'fill here your password';
            password1Msg.style.color = '#ddaa00';
        }
        if (confirmationInput.value === '') {
            confirmationInput.style.borderBottom = '4px solid #ddaa00';
            const password2Msg = document.querySelector('#register-pass2-msg');
            password2Msg.innerHTML = 'confirm here your password';
            password2Msg.style.color = '#ddaa00';
        }
        if (usernameInput.value === '' || firstNameInput === '' || 
            lastNameInput === '' || emailInput === '' ||
            passwordInput.value === '' || confirmationInput.value === ''
            )
        {
            return false
        }
        // Check passwords (password and confirmation password) equalty
        if (passwordInput.value !== confirmationInput.value) {
            passwordInput.style.borderBottom = '4px solid #f00';
            passwordInput.style.borderBottom = '4px solid #f00';
            const msg = document.querySelector('#register-pass2-msg');
            msg.innerHTML = 'passwords doesn\'t match';
            msg.style.color = '#f00';
            return false;
        }
        // Fetch
        const formData = new FormData();
        formData.append('username', usernameInput.value);
        formData.append('email', emailInput.value);
        formData.append('first_name', firstNameInput.value);
        formData.append('last_name', lastNameInput.value);
        formData.append('password', passwordInput.value);
        formData.append('confirmation', confirmationInput.value);

        setLoading(true);
        fetch('/register', {
            "method": "POST",
            "headers": {
                "X-CSRFToken": csrf_cookie[1]
            },
            "body": formData
        })
        .then(response => response.json())
        .then(response => {
            if (response.error_password) {
                passwordInput.style.borderBottom = '4px solid #f00';
                passwordInput.style.borderBottom = '4px solid #f00';
                const msg = document.querySelector('#register-pass2-msg');
                msg.innerHTML = response.error_password;
                msg.style.color = '#f00';
            }
            if (response.error_username) {
                usernameInput.style.borderBottom = '4px solid #ddaa00';
                const usernameMsg = document.querySelector('#register-username-msg');
                usernameMsg.innerHTML = response.error_username;
                usernameMsg.style.color = '#ddaa00';
            }
            if (response.user) {
                localStorage.setItem("logged_user", response.user);
                console.log(response.user);
                // Redirect logged user
                window.location.replace('/home');
            }
        })

        return false
    }

    function resetLooks() {
        clearMsgs();
        const usernameInput = document.querySelector('#register-username-input');
        const firstNameInput = document.querySelector('#register-first-input');
        const lastNameInput = document.querySelector('#register-last-input');
        const emailInput = document.querySelector('#register-email-input');
        const password1Input = document.querySelector('#register-pass1-input');
        const password2Input = document.querySelector('#register-pass2-input');

        if (usernameInput.value !== '') {
            usernameInput.style.borderBottom = '';
        }
        if (firstNameInput.value !== '') {
            firstNameInput.style.borderBottom = '';
        }
        if (lastNameInput.value !== '') {
            lastNameInput.style.borderBottom = '';
        }
        if (emailInput.value !== '') {
            emailInput.style.borderBottom = '';
        }
        if (password1Input.value !== '') {
            password1Input.style.borderBottom = '';
        }
        if (password2Input.value !== '') {
            password2Input.style.borderBottom = '';
        }
    }
    
    useEffect(() => {
        document.title = 'Register - Social Network';
    })

    return(
        <>
            <div className="center-group-container mt-5p">

                <h2>Register</h2>

                {is_loading ? (
                    <div className="lds-ring"><div></div><div></div><div></div><div></div></div>
                ) : (
                    <></>
                )}

                <form onSubmit={register} className='center-group-container' id='register-form'>
                    <div className="form-group center-group-container">
                        <input onChange={resetLooks} id='register-username-input' className="text-input-2" autoFocus type="text" name="username" placeholder="Username"/>
                        <div id='register-username-msg' className='msg-div'></div>
                    </div>
                    <div className="form-group center-group-container">
                        <input onChange={resetLooks} id='register-first-input' className="text-input-2" type="text" name="first_name" placeholder="First Name"/>
                        <div id='register-first-msg' className='msg-div'></div>
                    </div>
                    <div className="form-group center-group-container">
                        <input onChange={resetLooks} id='register-last-input' className="text-input-2" type="text" name="last_name" placeholder="Last Name"/>
                        <div id='register-last-msg' className='msg-div'></div>
                    </div>
                    <div className="form-group center-group-container">
                        <input onChange={resetLooks} id='register-email-input' className="text-input-2" type="email" name="email" placeholder="Email Address"/>
                        <div id='register-email-msg' className='msg-div'></div>
                    </div>
                    <div className="form-group center-group-container">
                        <input onChange={resetLooks} id='register-pass1-input' className="text-input-2 register-pass-input" type="password" name="password" placeholder="Password"/>
                        <TooglePassword input_selector={".register-pass-input"}/>
                        <div id='register-pass1-msg' className='msg-div'></div>
                    </div>
                    <div className="form-group  center-group-container">
                        <input onChange={resetLooks} id='register-pass2-input' className="text-input-2 register-pass-input" type="password" name="confirmation" placeholder="Confirm Password"/>
                        <div id='register-pass2-msg' className='msg-div'></div>
                    </div>
                    <input className="primary-btn my-2" type="submit" value="Register"/>
                </form>

                Already have an account? <Link className='teal-link' to="/login">Log In here.</Link>

            </div>
        </>
    );
}

export default Registerpage;