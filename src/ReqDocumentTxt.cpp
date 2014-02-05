
#include <fstream>

#include "ReqDocumentTxt.h"
#include "logging.h"
#include "req.h"

int ReqDocumentTxt::loadRequirements()
{
    init();

    LOG_DEBUG("loadText: %s", fileConfig.path.c_str());
    const int LINE_SIZE_MAX = 4096;
    char line[LINE_SIZE_MAX];

    std::ifstream ifs(fileConfig.path.c_str(), std::ifstream::in);

    currentRequirement = "";

    if (!ifs.good()) {
        LOG_ERROR("Cannot open file: %s", fileConfig.path.c_str());
        return -1;
    }

	int linenum = 1;
    while (ifs.getline(line, LINE_SIZE_MAX)) { // stop if line too long
        BlockStatus status = processBlock(line);
        if (status == STOP_REACHED) return 0;
		linenum++;
    }
	if (!ifs.eof()) {
		LOG_ERROR("Line too long in file '%s': %d (max size=%d)", fileConfig.path.c_str(), linenum, LINE_SIZE_MAX);
	}
    return 0;
}
