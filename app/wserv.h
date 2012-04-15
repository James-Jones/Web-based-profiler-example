#include "stats.h"
struct mg_context;

struct WebServer
{
    mg_context * Context;
};

void StartWebServer(Stats* stats, WebServer& ws, const char** options);
void StopWebServer(WebServer& ws);

