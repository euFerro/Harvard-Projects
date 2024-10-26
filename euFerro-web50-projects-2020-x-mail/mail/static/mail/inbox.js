document.addEventListener('DOMContentLoaded', function() {

  // Use buttons to toggle between views
  document.querySelector('#inbox').addEventListener('click', () => load_mailbox('inbox'))
  document.querySelector('#sent').addEventListener('click', () => load_mailbox('sent'))
  document.querySelector('#archived').addEventListener('click', () => load_mailbox('archive'))
  document.querySelector('#compose').addEventListener('click', compose_email)
  document.querySelector('#compose-form').onsubmit = send_email

  // By default, load the inbox
  load_mailbox('inbox')
})

function compose_email() {

  // Show compose view and hide other views
  document.querySelector('#emails-view').style.display = 'none'
  document.querySelector('#compose-view').style.display = 'block'
  document.querySelector('#email-view').style.display = 'none'

  // Clear out composition fields
  document.querySelector('#compose-recipients').value = ''
  document.querySelector('#compose-subject').value = ''
  document.querySelector('#compose-body').value = ''
}

function load_mailbox(mailbox) {
  
  // Show the mailbox and hide other views
  document.querySelector('#emails-view').style.display = 'block'
  document.querySelector('#compose-view').style.display = 'none'
  document.querySelector('#email-view').style.display = 'none'

  // Show the mailbox name
  document.querySelector('#emails-view').innerHTML = `<h3>${mailbox.charAt(0).toUpperCase() + mailbox.slice(1)}</h3>`;

  fetch(`/emails/${mailbox}`)
  .then(response => response.json())
  .then(emails => {
    // Print emails
    console.log(emails);
    emails_view = document.querySelector('#emails-view');
    emails_container = document.createElement('div');

    if (emails.length == 0) {
      const no_emails = document.createElement('div')
      no_emails.innerHTML = 'No emails yet.'
      no_emails.className += 'col'
      email_view.append(no_emails)

    } else {

      let new_count = 0
      emails.forEach(email => {
        entry = document.createElement('div')
        sender = document.createElement('div')
        strong = document.createElement('strong')
        strong.innerHTML = email.sender
        sender.append(strong)
        body = document.createElement('div')
        ts = document.createElement('div')
        body.innerHTML = email.subject
        ts.innerHTML = email.timestamp
        if (email.read) {
          entry.style.backgroundColor = 'lightgray'
        } else {
          new_count++
        }
        entry.append(sender)
        entry.append(body)
        entry.append(ts)
        entry.className += "row"
        sender.className += "col"
        body.className += "col"
        ts.className += "col timestamp"
        entry.className += ' email-entry'

        entry.addEventListener('click', () => {
          fetch(`/emails/${email.id}`)
          .then(response => response.json())
          .then(email => {
            show_email(email)
          })
        });
        emails_container.append(entry)
      })

      emails_view.append(emails_container);
      if (new_count > 0) {
        new_in = document.createElement('span')
        new_in.innerHTML = new_count
        new_in.className += "position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger"
        document.querySelector('#inbox').append(new_in)
      }
    }
  })
}

function send_email() {
  const recipients = document.querySelector('#compose-recipients').value
  const subject = document.querySelector('#compose-subject').value
  const body = document.querySelector('#compose-body').value

  fetch('/emails', {
    method: 'POST',
    body: JSON.stringify({
        recipients: recipients,
        subject: subject,
        body: body
    })
  })
  .then(response => response.json())
  .then(result => {
      // Print result
      console.log(result)
      if (result.error) {
        msg = document.querySelector('#form-msg')
        alert_error = document.createElement('div')
        alert_error.innerHTML = result.error
        alert_error.className += "alert alert-danger"
        msg.append(alert_error)
        return false
      }
      if (result.message) {
        alert(result.message)
        clear_inbox()
        load_mailbox('inbox')
      }
  })
  return true
}

function show_email(email) {
  document.querySelector('#emails-view').style.display = 'none'
  document.querySelector('#compose-view').style.display = 'none'
  document.querySelector('#email-view').style.display = 'block'

  // Remove all before displaying the email
  children = document.querySelector('#email-view').childNodes
  children.forEach(child => {
    child.remove()
  })
  // Mark as read
  fetch(`emails/${email.id}`, {
    method: 'PUT',
    body: JSON.stringify({
        read: true
    })
  });
  // Compose email view
  container = document.createElement('div')
  container.className = 'container'
  header = document.createElement('div')

  sender = document.createElement('h2')
  sender.innerHTML = 'Sender: ' + email.sender
  recipients = document.createElement('div')
  recipients.innerHTML = `recepient(s): ${email.recipients}`
  recipients.style.color = 'gray'

  ts = document.createElement('div')
  ts.innerHTML = email.timestamp
  ts.className += 'timestamp'

  hr = document.createElement('hr')

  subject = document.createElement('div')
  subject_title = document.createElement('h5')
  subject_title.innerHTML = `Subject: ${email.subject}`
  subject.className += 'subject'
  subject.append(subject_title)
  
  body = document.createElement('p')
  body_logo = document.createElement('h4')
  body_msg = document.createElement('p')
  body_logo.innerHTML = 'Message:'
  body_logo.style.color = 'blue'
  body_msg.innerHTML = email.body
  body.className += 'mail-message my-2'
  body.append(body_logo)
  body.append(body_msg)

  // Archive button
  if (email.archived === false) {
    archive_btn = document.createElement('button')
    archive_btn.innerHTML = 'archive'
    archive_btn.className += 'btn btn-success mx-2'
    archive_btn.addEventListener('click', () => {
      fetch(`emails/${email.id}`, {
        method: 'PUT',
        body: JSON.stringify({
          archived: true
        })
      })
      load_mailbox('inbox')
    });
  } else {
    archive_btn = document.createElement('button')
    archive_btn.innerHTML = 'unarchive'
    archive_btn.className += 'btn btn-secondary mx-2'
    archive_btn.addEventListener('click', () => {
      fetch(`emails/${email.id}`, {
        method: 'PUT',
        body: JSON.stringify({
          archived: false
        })
      })
      load_mailbox('inbox')
    });
  }

  reply = document.createElement('button')
  reply.innerHTML = "Reply"
  reply.className += 'btn btn-primary mx-2'
  reply.addEventListener('click', () => {
    compose_email()
    document.querySelector('#compose-recipients').value = email.sender
    document.querySelector('#compose-subject').value = email.subject
    document.querySelector('#compose-body').value = `On ${email.timestamp} ${email.sender} wrote: ${email.body}`
  });

  header.append(sender)
  header.append(recipients)
  header.append(ts)
  container.append(header)
  container.append(hr)
  container.append(subject)
  container.append(body)
  container.append(archive_btn)
  container.append(reply)
  document.querySelector('#email-view').append(container)
}
