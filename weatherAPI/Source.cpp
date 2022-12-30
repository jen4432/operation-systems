#include <iostream>
#include <fstream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/SharedPtr.h>
#include <Poco/JSON/PrintHandler.h>

using namespace std;

int main() {
	Poco :: URI uri("http://api.weather.yandex.ru/v2/forecast?lat=53.893869&lon=27.547153");

	Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

	session.setKeepAlive(true);

	string path(uri.getPathAndQuery());
	if (path.empty()) {
		path = "/";
	}

	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path);
	request.add("X-Yandex-API-Key", "d19adbed-6bd4-432e-b242-3c07b74b3e28");
	session.sendRequest(request);

	Poco::Net::HTTPResponse response;
	istream& fin = session.receiveResponse(response);


	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(fin);
	Poco::JSON::Object::Ptr fullobj = result.extract< Poco::JSON::Object::Ptr>();

	int now = fullobj->getValue<int>("now");
	string now_dt = fullobj->getValue<string>("now_dt");
	Poco::JSON::Object::Ptr info = fullobj->getObject("info");
	Poco::JSON::Object::Ptr fact = fullobj->getObject("fact");
	Poco::JSON::Object::Ptr forecasts = fullobj->getObject("forecasts");

	int temp = fact->getValue<int>("temp");

	int feels_like = fact->getValue<int>("feels_like");

	int temp_water = fact->getValue<int>("temp_water");

	string condition = fact->getValue<string>("condition");

	Poco::JSON::Object::Ptr tzinfo = info->getObject("tzinfo");
	string locality = tzinfo->getValue<string>("name");

	string season = fact->getValue<string>("season");

	cout << "Current temperature: " << temp << endl;
	cout << "Feels like: " << feels_like << endl;
	cout << "Current conditon: " << condition << endl;
	cout << "Current season: " << season << endl;
	cout << "Locality of query: " << locality << endl;
	cout << "Temp_water :" << temp_water << endl;
}