// Example derived from https://www.zenrows.com/blog/c-plus-plus-web-scraping#challenges
// Make headless info from https://github.com/durdyev/webdriverxx/issues/14

#include <iostream>
#include <vector>
#include <webdriverxx/webdriver.h>
#include <webdriverxx/browsers/chrome.h>
#include <fstream>
#include <webdriverxx/browsers/firefox.h>

using namespace webdriverxx;
struct Product {
    std::string url;
    std::string image;
    std::string name;
    std::string price;
};

int main() {
    // need to set Capabilites to --headless
    picojson::value json;
    std::string json_str(
            "{\"moz:firefoxOptions\":{"
            "\"args\":[\"--headless\"]"
            "}}"
    );
    std::string err;
    picojson::parse(json, json_str.begin(), json_str.end(), &err);
    Capabilities caps;
    CustomFromJson(json, caps);
    webdriverxx::WebDriver driver = Start(Firefox(caps));

    // visit the target page in the controlled browser
    driver.Navigate("https://www.scrapingcourse.com/ecommerce/");

    // perform an XPath query
    std::vector<Element> product_html_elements = driver.FindElements(ByXPath("//li[contains(@class, 'product')]"));

    // To store the scraped products
    std::vector<Product> products;

    // Iterate over the list of product HTML elements
    for (auto& product_html_element : product_html_elements) {
        std::string url = product_html_element.FindElement(ByXPath(".//a")).GetAttribute("href");
        std::string image = product_html_element.FindElement(ByXPath(".//a/img")).GetAttribute("src");
        std::string name = product_html_element.FindElement(ByXPath(".//a/h2")).GetText();
        std::string price = product_html_element.FindElement(ByXPath(".//a/span")).GetText();

        Product product = {url, image, name, price};
        products.push_back(product);
    }

    // create the CSV file of output
    std::ofstream csv_file("products.csv");

    // populate it with the header
    csv_file << "url,image,name,price" << std::endl;

    // populate the CSV output file
    for (int i = 0; i < products.size(); ++i) {
        // transform a Product instance to a
        // CSV string record
        Product p = products.at(i);
        std::string csv_record = p.url + "," + p.image + "," + p.name + "," + p.price;
        csv_file << csv_record << std::endl;
    }

    // free up the resources for the CSV file
    csv_file.close();

    return 0;
}
