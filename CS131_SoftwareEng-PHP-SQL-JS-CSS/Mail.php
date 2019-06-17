<?php

require_once "config/config.php";

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;


/**
 * Sends the student an emailed receipt.
 */
class Mail {

    static function sendReciept($student_email, $msg) {

        $mail = new PHPMailer(true);

        try {
            $mail->isSMTP();
            $mail->Host = 'ssl://smtp.gmail.com';  // Specify main and backup SMTP servers
            $mail->SMTPAuth = true;  // Enable SMTP authentication
            $mail->Username = G_EMAIL_NAME; // SMTP username
            $mail->Password = G_EMAIL_PASS; // SMTP password
            $mail->SMTPSecure = 'ssl'; // Enable TLS encryption, `ssl` also accepted
            $mail->Port = 465;  // TCP port to connect to

            //Recipients
            $mail->setFrom(G_EMAIL_NAME, 'Attendance Tracker');
            $mail->addAddress($student_email);     // Add a recipient

            //Content
            $mail->isHTML(true);
            $mail->Subject = 'CSC 131 Attendance Receipt';
            $mail->Body    = $msg;
            $mail->AltBody = $msg;

            $mail->send();

        } catch (Exception $e) {
            echo 'Message could not be sent.';
            echo 'Mailer Error: ' . $mail->ErrorInfo;
        }

    }
}