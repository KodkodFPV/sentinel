#pragma once

/**
 * @file
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Internal hexdump formatting helpers.
 */

#include <cstdint>
#include <cstddef>


namespace sentinel::detail
{
  inline constexpr std::size_t HexdumpGroupSize       = 8;
  inline constexpr std::size_t HexdumpGroupCount      = 4;
  inline constexpr std::size_t HexdumpLineDataSize    = HexdumpGroupSize * HexdumpGroupCount;
  inline constexpr std::size_t HexdumpHEXBufferSize   = HexdumpGroupCount * (HexdumpGroupSize * 3 - 1) + (HexdumpGroupCount - 1) * 2 + 1;
  inline constexpr std::size_t HexdumpASCIIBufferSize = HexdumpGroupCount * HexdumpGroupSize + (HexdumpGroupCount - 1) + 1;

  inline constexpr char HexdumpColumnHeader[] =
    "          "
    "00 01 02 03 04 05 06 07  "
    "08 09 0A 0B 0C 0D 0E 0F  "
    "10 11 12 13 14 15 16 17  "
    "18 19 1A 1B 1C 1D 1E 1F";

  inline constexpr char HexdumpNullLine[] =
    "          "
    "<null>";

  inline constexpr char HexdumpHexDigits[] =
    "0123456789ABCDEF";

  inline constexpr std::uint8_t HexdumpHighNibbleMask = 0xF0;
  inline constexpr std::uint8_t HexdumpLowNibbleMask  = 0x0F;
  inline constexpr std::uint8_t HexdumpBitsPerNibble  = 4;
  inline constexpr std::uint8_t HexdumpPrintableFirst = ' ';
  inline constexpr std::uint8_t HexdumpPrintableLast  = '~';

  template <std::size_t Size>
    class HEXBuffer
    {
      public:
        void add(char value)
        {
          *m_pos++ = value;
        }

        void add(char value, std::size_t count)
        {
          while (count-- > 0)
            add(value);
        }

        void addByte(std::uint8_t value)
        {
          add(HexdumpHexDigits[(value & HexdumpHighNibbleMask) >> HexdumpBitsPerNibble]);
          add(HexdumpHexDigits[value & HexdumpLowNibbleMask]);
        }

        void addGroup(const std::uint8_t* bytes, std::size_t size, std::size_t groupSize)
        {
          for (std::size_t column = 0; column < groupSize; ++column)
          {
            if (column < size)
              addByte(bytes[column]);
            else
              add(' ', 2);

            if (column + 1 < groupSize)
              add(' ');
          }
        }

        const char* c_str()
        {
          *m_pos = '\0';

          return m_data;
        }

      private:
        char  m_data[Size]{};
        char* m_pos = m_data;
    };

  template <std::size_t Size>
    class ASCIIBuffer
    {
      public:
        void add(char value)
        {
          *m_pos++ = value;
        }

        void add(char value, std::size_t count)
        {
          while (count-- > 0)
            add(value);
        }

        void addByte(std::uint8_t value)
        {
          add(asciiChar(value));
        }

        void addGroup(const std::uint8_t* bytes, std::size_t size, std::size_t groupSize)
        {
          for (std::size_t column = 0; column < groupSize; ++column)
          {
            if (column < size)
              addByte(bytes[column]);
            else
              add(' ');
          }
        }

        const char* c_str()
        {
          *m_pos = '\0';

          return m_data;
        }

      private:
        static constexpr char asciiChar(std::uint8_t value)
        {
          return value >= HexdumpPrintableFirst && value <= HexdumpPrintableLast ? static_cast<char>(value) : '.';
        }

        char  m_data[Size]{};
        char* m_pos = m_data;
    };

  template <typename LogF>
    inline void log_hexdump(LogF&& log, const char* tag, const char* label, const void* data, std::size_t size)
    {
      log(tag, "%s, size %zu", label, size);

      if (size == 0)
        return;

      if (!data)
      {
        log(tag, "%s", HexdumpNullLine);
        return;
      }

      log(tag, "%s", HexdumpColumnHeader);

      auto bytes = static_cast<const std::uint8_t*>(data);

      for (std::size_t offset = 0; offset < size; offset += HexdumpLineDataSize)
      {
        HEXBuffer<HexdumpHEXBufferSize>     hexBuffer;
        ASCIIBuffer<HexdumpASCIIBufferSize> asciiBuffer;

        auto left = size - offset;
        if (left > HexdumpLineDataSize)
          left = HexdumpLineDataSize;

        for (std::size_t group = 0; group < HexdumpGroupCount; ++group)
        {
          auto count = left > HexdumpGroupSize ? HexdumpGroupSize : left;

          hexBuffer.addGroup(bytes, count, HexdumpGroupSize);
          asciiBuffer.addGroup(bytes, count, HexdumpGroupSize);

          if (group + 1 < HexdumpGroupCount)
          {
            hexBuffer.add(' ', 2);
            asciiBuffer.add(' ');
          }

          bytes += count;
          left -= count;
        }

        log(tag, "%08zX: %s  |%s|", offset, hexBuffer.c_str(), asciiBuffer.c_str());
      }
    }
}
