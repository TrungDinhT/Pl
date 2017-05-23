#include "notes.h"

Article::Article(const QString& ti, const QString& te): Note(ti), text(te){ setId(createID()); }
Article::Article(const QString& i, const QString& ti, const QString& te): Note(ti), text(te){ setId(i); }
