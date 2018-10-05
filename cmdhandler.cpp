#include "cmdhandler.h"
#include "util.h"
using namespace std;

/********* QUIT **********************************/


QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, 
	std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

/********* AND **********************************/

AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, 
	std::istream& instr) const
{	
	string term;
	vector<string> terms;
	while(instr >> term)
	{
		terms.push_back(term);
	}
	vector<Tweet*> car = eng->search(terms, 0);
	displayHits(car);
	return HANDLER_OK;
}


/********* OR **********************************/

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, 
	std::istream& instr) const
{
	string term;
	vector<string> terms;
	while(instr >> term)
	{
		terms.push_back(term);
	}
	vector<Tweet*> car = eng->search(terms, 1);
	displayHits(car);
	return HANDLER_OK;
}

/********* TWEET **********************************/

TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, 
	std::istream& instr) const
{
	//string username, 
	string tweet_text;
	//instr >> username;
	//if (instr.fail()) return HANDLER_ERROR;
	if(! getline(instr,tweet_text)) return HANDLER_ERROR;

	tweet_text = tweet_text.erase(0, 1);
	eng->addTweet(tweet_text);
	return HANDLER_OK;
}


/********* FOLLOW **********************************/

FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
  : Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, 
	std::istream& instr) const
{
	string toFollow; //follower
	// instr >> follower;
	instr >> toFollow;
	eng->addFollower(toFollow);
	return HANDLER_OK;
}


/********* SAVE **********************************/

SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
  : Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, 
	std::istream& instr) const
{
	string filename;
	instr >> filename;
	eng->save(filename);
	return HANDLER_OK;
}


/********* SCC **********************************/

SCCHandler::SCCHandler()
{

}

SCCHandler::SCCHandler(Handler* next)
  : Handler(next)
{

}

bool SCCHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SCC";
}

Handler::HANDLER_STATUS_T SCCHandler::process(TwitEng* eng, 
	std::istream& instr) const
{	
	string filename;
	instr >> filename;
	eng->SCC(filename);
	return HANDLER_OK;
}

/********* TrendingHandler **********************************/

TrendingHandler::TrendingHandler()
{

}

TrendingHandler::TrendingHandler(Handler* next)
  : Handler(next)
{

}

bool TrendingHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TRENDING";
}

Handler::HANDLER_STATUS_T TrendingHandler::process(TwitEng* eng, 
	std::istream& instr) const
{	
	int n;
	instr >> n;
	eng->trending(n);
	return HANDLER_OK;
}

/********* LOGINHANDLER **********************************/

LoginHandler::LoginHandler()
{

}

LoginHandler::LoginHandler(Handler* next)
  : Handler(next)
{

}

bool LoginHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGIN";
}

Handler::HANDLER_STATUS_T LoginHandler::process(TwitEng* eng, 
	std::istream& instr) const
{	
	string username, password;
	instr >> username;
	instr >> password;
	if(eng->login(username, password)) 
		return HANDLER_ERROR;
	return HANDLER_OK;
}

/********* LOGOUTHANDLER **********************************/

LogoutHandler::LogoutHandler()
{

}

LogoutHandler::LogoutHandler(Handler* next)
  : Handler(next)
{

}

bool LogoutHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGOUT";
}

Handler::HANDLER_STATUS_T LogoutHandler::process(TwitEng* eng, 
	std::istream& instr) const
{	
	eng->logout();
	return HANDLER_OK;
}