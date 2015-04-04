package jp.developerwaiwai.simple.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

@Controller
@RequestMapping("/")
public class MyHomeController {

    private final String internalURL = "http://192.168.XXX.XXX:8080/on";

    @RequestMapping("light")
    @ResponseBody
    public String index() throws MalformedURLException {

        int responce = requestHttp(internalURL);

        String returnValue = "NG";
        if (responce == HttpURLConnection.HTTP_OK) {

            returnValue = "OK";

        }
        else {

            returnValue += " responce=" + String.valueOf(responce);

        }

        return returnValue;
    }

    private int requestHttp(String urlString) throws MalformedURLException {

        int responce = HttpURLConnection.HTTP_BAD_REQUEST;

        URL url = new URL(urlString);

        HttpURLConnection connection = null;

        try {
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");

            responce = connection.getResponseCode();


        } catch (Exception e) {
            e.printStackTrace();

        } finally {

            if (connection != null) {

                connection.disconnect();

            }

        }

        return responce;

    }

}
