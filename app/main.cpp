#include <stddef.h>
#include <stdio.h>
#include "wserv.h"

void main()
{
	Stats stats;
	WebServer ws;
	int x;

    const char* mongoose_config [] = {
        "num_threads", "2",
        "document_root", ".",
        NULL
    };

	stats.pszMessage = "Some text from C++ app!";
	stats.fFramesPerSecond = 100.0;
	stats.iLastFrameStartTimeMilliSeconds = 1000/stats.fFramesPerSecond;

	StartWebServer(&stats, ws, mongoose_config);

	printf("Press any key to quit");
	scanf("%x", &x);

	StopWebServer(ws);
}
