#include "wserv.h"
#include <mongoose.h>

void * mongoose_callback(enum mg_event event,
                         struct mg_connection *conn,
                         const struct mg_request_info *request_info);

void StartWebServer(Stats* stats, WebServer& ws, const char** options)
{
    mg_context * Context = mg_start( mongoose_callback, (void*)stats, options );
    ws.Context = Context;
}
void StopWebServer(WebServer& ws)
{
    mg_stop(ws.Context);
}

#include <cstring>

void * mongoose_callback(enum mg_event event,
                         struct mg_connection *conn,
                         const struct mg_request_info *request_info)
{
    void *processed = "yes";

    switch( event )
    {
        case MG_NEW_REQUEST:
        {
            if(strcmp( request_info->uri, "/frame_rate" ) == 0)
            {
                Stats* stats = (Stats*)request_info->user_data;
                mg_printf( conn,
                    "HTTP/1.0 200 OK\r\n"
                    "Content-Type: text/json \r\n\r\n" // Two lines to end the header
                    "{ \"frame_rate\" : \"%f\" }",
                    stats->fFramesPerSecond
                );
                return processed; // We're done, tell mongoose
            }

            if(strcmp( request_info->uri, "/message_box" ) == 0)
            {
                Stats* stats = (Stats*)request_info->user_data;
                mg_printf( conn,
                    "HTTP/1.0 200 OK\r\n"
                    "Content-Type: text/json \r\n\r\n" // Two lines to end the header
                    "{ \"message_box\" : \"%s\" }",
                    stats->pszMessage
                );
                return processed; // We're done, tell mongoose
            }
        }
        break;
        case MG_HTTP_ERROR:
        {
        }
        break;
        case MG_EVENT_LOG:
        {
        }
        break;
        case MG_INIT_SSL:
        {
        }
        break;
        default:
        {
        }
        break;
    }

    return 0; // Nothing done here, proceed with default behavior
}

