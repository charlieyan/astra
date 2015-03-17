#ifndef STREAM_H
#define STREAM_H

namespace sensekit {

    class StreamSource;

    class Stream
    {
    public:
        Stream(StreamSource& source)
            : m_source(source) { }

        void open();
        void close();


    protected:
        StreamSource& m_source;

    };


}


#endif /* STREAM_H */