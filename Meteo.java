import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.net.URL;
import java.net.URLConnection;

public class Meteo {
    public static void main(String[] args) {
        try {
            URL url = new URL("https://api.openweathermap.org/data/2.5/weather?q=Paris&appid=c42d5a772f3a65461a08f1ef8eb57fc4");
            URLConnection connection = url.openConnection();
            InputStream stream = connection.getInputStream();

            BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
            StringBuilder result = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                result.append(line);
            }
            Object obj = JSONValue.parse(result.toString());
            JSONObject json = (JSONObject) obj ;
            JSONObject mainJson = (JSONObject) json.get("main");
            double temp = (Double) (mainJson.get("temp"))-273.15;
            BigDecimal bd = new BigDecimal(String.valueOf(temp)).setScale(0, RoundingMode.HALF_UP);
            System.out.println("Current temperature in Paris: " + bd +"°C");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
