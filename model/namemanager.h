#pragma once

#include <QSet>
#include <QString>




class NameManager
{

public:

    bool is_available(const QString& name) const
    {
        return !all_names.contains(name);
    }

    bool is_taken(const QString& name) const
    {
        return all_names.contains(name);
    }

    void take_name(const QString& name)
    {
        Q_ASSERT(!all_names.contains(name));
        all_names.insert(name);
    }

    QString next_available(const QString& base) const
    {
        QString name;

        for (int i = 1; true; ++i)
        {
            name = base + QString::number(i);
            if (is_available(name))
            {
                return name;
            }
        }
    }

    // Finds the next available name, takes and returns it.
    QString take_next_available(const QString& base)
    {
        QString name = next_available(base);
        take_name(name);
        return name;
    }

    // Releases the name, so it can be used again
    void release_name(const QString& name)
    {
        assert(all_names.contains(name));
        all_names.remove(name);
    }

    qint64 unique_id()
    {
        return next_available_id++;
    }

    bool is_valid(qint64 id) const
    {
        return id >= START_ID && id < next_available_id;
    }

private:

    static constexpr qint64 START_ID = 1001;

    QSet<QString> all_names;
    qint64 next_available_id = START_ID;

};
