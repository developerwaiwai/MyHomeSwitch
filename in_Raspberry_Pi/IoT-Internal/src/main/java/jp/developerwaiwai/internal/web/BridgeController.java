package jp.developerwaiwai.internal.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.io.IOException;


@Controller
@RequestMapping("/")
public class BridgeController {


    @RequestMapping("on")
    @ResponseBody
    public String bridgeOn() {


        ProcessBuilder pb = new ProcessBuilder("sudo", "/home/pi/serial-on");
        pb.redirectErrorStream(true);

        try {

            Process process = pb.start();

        } catch (IOException e) {

            e.printStackTrace();

        }

        return "OK";
    }

}
