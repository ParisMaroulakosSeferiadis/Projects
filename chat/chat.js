"use strict";

$(document).ready(function () {
    var chatInterval = 100; //refresh interval in ms
    var $userName = $("#userName");
    var $chatOutput = $("#chatOutput");
    var $chatInput = $("#chatInput");
    var $chatSend = $("#chatSend");

    function sendMessage() {
        var userNameString = $userName.val();
        var chatInputString = $chatInput.val();

        $.get("./write.php", {
            username: userNameString,
            text: chatInputString
        });

        $userName.val("");
        retrieveMessages();
    }

    function retrieveMessages() {
        $.get("./read.php", function (data) {
            $chatOutput.html(data); //Paste content into chat output
        });
    }


    $chatSend.click(function () {
        sendMessage();
    });

    setInterval(function () {
        retrieveMessages();
    }, chatInterval);
});