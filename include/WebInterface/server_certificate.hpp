//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_EXAMPLE_COMMON_SERVER_CERTIFICATE_HPP
#define BOOST_BEAST_EXAMPLE_COMMON_SERVER_CERTIFICATE_HPP

#include <boost/asio/buffer.hpp>
#include <boost/asio/ssl/context.hpp>
#include <cstddef>
#include <memory>

/*  Load a signed certificate into the ssl context, and configure
    the context for use with a server.

    For this to work with the browser or operating system, it is
    necessary to import the "Beast Test CA" certificate into
    the local certificate store, browser, or operating system
    depending on your environment Please see the documentation
    accompanying the Beast certificate for more details.
*/
inline
void
load_server_certificate(boost::asio::ssl::context& ctx)
{
    /*
        The certificate was generated from CMD.EXE on Windows 10 using:

        winpty openssl dhparam -out dh.pem 2048
        winpty openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 10000 -out cert.pem -subj "//C=US\ST=CA\L=Los Angeles\O=Beast\CN=www.example.com"
    */



        std::string const cert ="-----BEGIN CERTIFICATE-----\n"
                                "MIIFDjCCAvagAwIBAgIUQnQyolwLzcM0mmFJI0RkiJG2uckwDQYJKoZIhvcNAQEL\n"
                                "BQAwbjELMAkGA1UEBhMCR0IxDzANBgNVBAgMBlN1cnJleTEPMA0GA1UEBwwGTG9u\n"
                                "ZG9uMSAwHgYDVQQKDBdBbGdlYnJhaWMgU29sdXRpb25zIEx0ZDEbMBkGA1UEAwwS\n"
                                "QWxnZWJyYWljU29sdXRpb25zMB4XDTIwMDgxNzEyMDkxMFoXDTIxMDgxMjEyMDkx\n"
                                "MFowgZYxCzAJBgNVBAYTAmdiMQ8wDQYDVQQIDAZTdXJyZXkxIDAeBgNVBAoMF0Fs\n"
                                "Z2VicmFpYyBTb2x1dGlvbnMgTHRkMRswGQYDVQQDDBJBbGdlYnJhaWNTb2x1dGlv\n"
                                "bnMxNzA1BgkqhkiG9w0BCQEWKHRoZW4gd2UgbmVlZCB0byB1c2UgdGhlIHByaXZh\n"
                                "dGUga2V5IHRvIC4wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC1xFn0\n"
                                "hOqvu4SYdiJQYwT2uH3XL2ie1CQPybQn0KlDddt9Y/0gbYOFM+AXG8n2IL5Tq93D\n"
                                "Nd8mCNEz7qv4Xe6NlRr3rlimGLce+Dnlei+Z1mXMpJ79dMkWqaU2KgSElTrS4mxR\n"
                                "LTRa/8zP+lbllE8weUXOgpxfr0lblXbjB76LyYvpDBwogc+LJluaD6IbMysX2jyY\n"
                                "REwxjnyRgQJL9sOjOjmPVL9F/z6M9tQPiVp7mNcMhKiVj6tLpdxQV4pNr6/PQjiu\n"
                                "KGx2TTc60fG9wzcVeGaYhvX3nHQQ6QbJuGqzKaNjOkHM8pPFn+yTwZQA1iCul3z1\n"
                                "UJtgVwXhMsj35M4JAgMBAAGjezB5MAkGA1UdEwQCMAAwLAYJYIZIAYb4QgENBB8W\n"
                                "HU9wZW5TU0wgR2VuZXJhdGVkIENlcnRpZmljYXRlMB0GA1UdDgQWBBS8JEab0bz7\n"
                                "on2aUMmz0bkkvMlb3jAfBgNVHSMEGDAWgBRoz/JXCk0tTfZfC1QeZdL36y7BRzAN\n"
                                "BgkqhkiG9w0BAQsFAAOCAgEAY/eAutfY2BEOOsySSzEb5zrePzFT9UJ+6ISnUdHe\n"
                                "yqe5Km7MnosId8+ngcA4R2tJLdsO8ZGNlPPQFh77WPKJHV2vjeGlyMTJ5hJ9SWne\n"
                                "NwnWadzXuXM6knqBl3ZFa6M0eYQTkBtBC03vAQSDFjXj0sOsnrVeQM8tsolsxEa6\n"
                                "3SdKBvepRztcHaikOyOUNp1Fkoxil/mm3134/nP7H6F0+ueu/laOniCkOi3P+Yi1\n"
                                "WlnxM5d7t3YrehLt0RrWLnOcnL/Yh0U+42aQ7wxlHGnKcl+6+kxQIhyy6AQNr5zl\n"
                                "EkyUuTS4bPE6Ymg/zrQKjCFmbWqGelHHlt0TAHpYUIz1cDAa8xEsb0b09azdGGPI\n"
                                "6B04E//y/ggygt7qbU1SKrerVJcKKCUI3JaOELQfNy0uWTf9FTQMe1WrLNqrgFic\n"
                                "QsR7D10sEiMyqlZlVtl9FIYVJaNGSUXgzdyg4EKiAhx6F4Fge7gxjAkry2GTCH5i\n"
                                "lrXPjoYCgC5UonSLnrJqMwpSeFgchiZcld58Va4wE1rCFo7bkKxPeVz+XLI+dnh0\n"
                                "K4uwuNz0JC/sjLbATdJWCM2TxphiYXSqPY+nx8JogyssV7vJhZo7w0ejxRLJxubR\n"
                                "htrMSH/aOxg4IQk9vBk8fcboR4KXoJ673k4U4iXoBCdi5RL/qR0XLxCFqFkyVtuG\n"
                                "Hqk=\n"
                                "-----END CERTIFICATE-----\n";



/*    std::string const cert =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDaDCCAlCgAwIBAgIJAO8vBu8i8exWMA0GCSqGSIb3DQEBCwUAMEkxCzAJBgNV\n"
        "BAYTAlVTMQswCQYDVQQIDAJDQTEtMCsGA1UEBwwkTG9zIEFuZ2VsZXNPPUJlYXN0\n"
        "Q049d3d3LmV4YW1wbGUuY29tMB4XDTE3MDUwMzE4MzkxMloXDTQ0MDkxODE4Mzkx\n"
        "MlowSTELMAkGA1UEBhMCVVMxCzAJBgNVBAgMAkNBMS0wKwYDVQQHDCRMb3MgQW5n\n"
        "ZWxlc089QmVhc3RDTj13d3cuZXhhbXBsZS5jb20wggEiMA0GCSqGSIb3DQEBAQUA\n"
        "A4IBDwAwggEKAoIBAQDJ7BRKFO8fqmsEXw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcF\n"
        "xqGitbnLIrOgiJpRAPLy5MNcAXE1strVGfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7b\n"
        "Fu8TsCzO6XrxpnVtWk506YZ7ToTa5UjHfBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO\n"
        "9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wWKIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBp\n"
        "yY8anC8u4LPbmgW0/U31PH0rRVfGcBbZsAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrv\n"
        "enu2tOK9Qx6GEzXh3sekZkxcgh+NlIxCNxu//Dk9AgMBAAGjUzBRMB0GA1UdDgQW\n"
        "BBTZh0N9Ne1OD7GBGJYz4PNESHuXezAfBgNVHSMEGDAWgBTZh0N9Ne1OD7GBGJYz\n"
        "4PNESHuXezAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQCmTJVT\n"
        "LH5Cru1vXtzb3N9dyolcVH82xFVwPewArchgq+CEkajOU9bnzCqvhM4CryBb4cUs\n"
        "gqXWp85hAh55uBOqXb2yyESEleMCJEiVTwm/m26FdONvEGptsiCmF5Gxi0YRtn8N\n"
        "V+KhrQaAyLrLdPYI7TrwAOisq2I1cD0mt+xgwuv/654Rl3IhOMx+fKWKJ9qLAiaE\n"
        "fQyshjlPP9mYVxWOxqctUdQ8UnsUKKGEUcVrA08i1OAnVKlPFjKBvk+r7jpsTPcr\n"
        "9pWXTO9JrYMML7d+XRSZA1n3856OqZDX4403+9FnXCvfcLZLLKTBvwwFgEFGpzjK\n"
        "UEVbkhd5qstF6qWK\n"
        "-----END CERTIFICATE-----\n";
*/

    std::string const key =
                            "-----BEGIN RSA PRIVATE KEY-----\n"
                            "Proc-Type: 4,ENCRYPTED\n"
                            "DEK-Info: AES-256-CBC,764696BF04FA2777E05520BBCE1E9CD9\n"
                            "6PRmvnO+hoF4Ue+QnNCizhFoEnZd0EtqKrUjgebAZjkrQuy59637G1/qbhoaoRl2\n"
                            "mF4i3HpXzwmFEkLALOS2V8Xg2mcE5608nDDZbygn9eqQf+Onwk+w1liPTyEODLgP\n"
                            "BqQBY+9ERIv4IwVd8GcvV2Xz00dcZIcefqG5cgc84dBE25xLr8111jv3kXIJJs8i\n"
                            "gWeY+LSNxRhjTJuRu8Np6NbJ2gtoC3m0TlY8PZ0g9biYRYuBuqsA+OVtJQwnJbLU\n"
                            "DCbCnjYuY9pywyJea5RiphGvnV04AmZ8CTylDNw5Swi1Is8CpkhXVvK9ktpyLW0P\n"
                            "npp7/7rv8LdrHKJWd0vzuFy0TP0e04rMhnQndokbPtZ1EzR9wjHsi7wKzYLb4rKO\n"
                            "UFAHNeFgQLDi7ww70LuM3jGLTO6o+ROtbWBIWRjdpfDvB94zVtDqLAaM0Kp7/JdN\n"
                            "3IF5kVrjJbepyrj8BmU9hUIEUteKz39XCLtIcX6c5i3Ky88DHj8fMLPRPgZjq+51\n"
                            "TWiVRlzE1gFU1StMEIxNHCqkNbUwFRdCDA9q3iPgRClO+T30QoL38uBkzdjaGz3c\n"
                            "57QkG5hb8WTELzXoO9q0AWsmxdD0lZ1u3KbgdzBj7K363ZSxIxiEyMr5Mp9gCSTU\n"
                            "7AQGV64gWjBBcpik303W/i2rPgfU+8VV+B6gMlJsqEXOvVjFhDQPvGSqKSyxNT2k\n"
                            "Kkxyqkgk2mXHKL/M1nJNwY6eQZkNxZHjs9u5FOHYjgBNGlBubgxpOhW7D9k6Ywcv\n"
                            "vcUx3z/P+WhpYGcn6C5fEY6s4js/XrzZs6MU3jtYYkgZcsDBMnLZgFQ3/L8F36W7\n"
                            "lbN9y0jxJXFCMVtc4vOIVXBo1cPKR83VhIyY4DXk5dPqmluxerLKcgNfWDbNmti3\n"
                            "0B2g40FRhjYN2mwx41XCA5lPC5TxIJJY6rJa3OQ3Sopa1uey/8AhBIzt+jxt/7Gm\n"
                            "u19tzpnGjBurZnOYnJulLTCoZyO4sOZlMgM8jxXDN7DDyO8yvoR71Pc6DGRydbLk\n"
                            "JLeLwHHgWZwrMl8E4hds+j1G3fW/wDV65M1tJEmtunrsPSg9aTerVUkhN0BxNB3X\n"
                            "nkaG3eIVyPQPK4ofIkYazyo3DwXx3AzadLHYUiI/d4Wr9mEemhIrouiu0LvFT+vZ\n"
                            "qP7UO4z1G0mmCYyv3eHHr7Kk9RBf/2sI8eoDhpcFpRz7jHe0ZKn3qHa/uHuy5luw\n"
                            "c7BCidJilRMe+xC6S5ENQT6Uqd7SsytAngrhSWi5N9iCwKDTfPrQFylhkZvmA+BJ\n"
                            "4mZpjYkD6lMNpBqStuT5jIC4AMhVtm5z4ptGT00V3ut+O4f+n0WiyvqckYorjONN\n"
                            "prHoflNYYk5Wp3F5qAcYUpmPTrqf1dofAtROQW0HDRyX7svZR77fLnaaMegRCUgP\n"
                            "EFoXbw7Uv8uY/VoU7mL+4ehsoHgiTzhKc4d38SP+GKh6gUkDs2FydyPMLj46F0P4\n"
                            "XxOz8DSWZhhJ7gAlHmZ8T+5yDfQdwdPYPeP+vSE01uef6iJmK4VM3tHdZm5b4wmg\n"
                            "k/sf43mMgfo/Bb7NWU9MX32c1ISB0b0uLiLfwJWUI2s/vmZBqX400ZZiArpSwefH\n"
                            "-----END RSA PRIVATE KEY-----\n";


/*    std::string const key =
        "-----BEGIN PRIVATE KEY-----\n"
        "MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDJ7BRKFO8fqmsE\n"
        "Xw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcFxqGitbnLIrOgiJpRAPLy5MNcAXE1strV\n"
        "GfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7bFu8TsCzO6XrxpnVtWk506YZ7ToTa5UjH\n"
        "fBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wW\n"
        "KIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBpyY8anC8u4LPbmgW0/U31PH0rRVfGcBbZ\n"
        "sAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrvenu2tOK9Qx6GEzXh3sekZkxcgh+NlIxC\n"
        "Nxu//Dk9AgMBAAECggEBAK1gV8uETg4SdfE67f9v/5uyK0DYQH1ro4C7hNiUycTB\n"
        "oiYDd6YOA4m4MiQVJuuGtRR5+IR3eI1zFRMFSJs4UqYChNwqQGys7CVsKpplQOW+\n"
        "1BCqkH2HN/Ix5662Dv3mHJemLCKUON77IJKoq0/xuZ04mc9csykox6grFWB3pjXY\n"
        "OEn9U8pt5KNldWfpfAZ7xu9WfyvthGXlhfwKEetOuHfAQv7FF6s25UIEU6Hmnwp9\n"
        "VmYp2twfMGdztz/gfFjKOGxf92RG+FMSkyAPq/vhyB7oQWxa+vdBn6BSdsfn27Qs\n"
        "bTvXrGe4FYcbuw4WkAKTljZX7TUegkXiwFoSps0jegECgYEA7o5AcRTZVUmmSs8W\n"
        "PUHn89UEuDAMFVk7grG1bg8exLQSpugCykcqXt1WNrqB7x6nB+dbVANWNhSmhgCg\n"
        "VrV941vbx8ketqZ9YInSbGPWIU/tss3r8Yx2Ct3mQpvpGC6iGHzEc/NHJP8Efvh/\n"
        "CcUWmLjLGJYYeP5oNu5cncC3fXUCgYEA2LANATm0A6sFVGe3sSLO9un1brA4zlZE\n"
        "Hjd3KOZnMPt73B426qUOcw5B2wIS8GJsUES0P94pKg83oyzmoUV9vJpJLjHA4qmL\n"
        "CDAd6CjAmE5ea4dFdZwDDS8F9FntJMdPQJA9vq+JaeS+k7ds3+7oiNe+RUIHR1Sz\n"
        "VEAKh3Xw66kCgYB7KO/2Mchesu5qku2tZJhHF4QfP5cNcos511uO3bmJ3ln+16uR\n"
        "GRqz7Vu0V6f7dvzPJM/O2QYqV5D9f9dHzN2YgvU9+QSlUeFK9PyxPv3vJt/WP1//\n"
        "zf+nbpaRbwLxnCnNsKSQJFpnrE166/pSZfFbmZQpNlyeIuJU8czZGQTifQKBgHXe\n"
        "/pQGEZhVNab+bHwdFTxXdDzr+1qyrodJYLaM7uFES9InVXQ6qSuJO+WosSi2QXlA\n"
        "hlSfwwCwGnHXAPYFWSp5Owm34tbpp0mi8wHQ+UNgjhgsE2qwnTBUvgZ3zHpPORtD\n"
        "23KZBkTmO40bIEyIJ1IZGdWO32q79nkEBTY+v/lRAoGBAI1rbouFYPBrTYQ9kcjt\n"
        "1yfu4JF5MvO9JrHQ9tOwkqDmNCWx9xWXbgydsn/eFtuUMULWsG3lNjfst/Esb8ch\n"
        "k5cZd6pdJZa4/vhEwrYYSuEjMCnRb0lUsm7TsHxQrUd6Fi/mUuFU/haC0o0chLq7\n"
        "pVOUFq5mW8p0zbtfHbjkgxyF\n"
        "-----END PRIVATE KEY-----\n";
*/

    std::string const dh =
        "-----BEGIN DH PARAMETERS-----\n"
        "MIIBCAKCAQEArzQc5mpm0Fs8yahDeySj31JZlwEphUdZ9StM2D8+Fo7TMduGtSi+\n"
        "/HRWVwHcTFAgrxVdm+dl474mOUqqaz4MpzIb6+6OVfWHbQJmXPepZKyu4LgUPvY/\n"
        "4q3/iDMjIS0fLOu/bLuObwU5ccZmDgfhmz1GanRlTQOiYRty3FiOATWZBRh6uv4u\n"
        "tff4A9Bm3V9tLx9S6djq31w31Gl7OQhryodW28kc16t9TvO1BzcV3HjRPwpe701X\n"
        "oEEZdnZWANkkpR/m/pfgdmGPU66S2sXMHgsliViQWpDCYeehrvFRHEdR9NV+XJfC\n"
        "QMUk26jPTIVTLfXmmwU0u8vUkpR7LQKkwwIBAg==\n"
        "-----END DH PARAMETERS-----\n";
    
    ctx.set_password_callback(
        [](std::size_t,
            boost::asio::ssl::context_base::password_purpose)
        {
            return "test";
        });

    ctx.set_options(
        boost::asio::ssl::context::default_workarounds |
        boost::asio::ssl::context::no_sslv2 |
        boost::asio::ssl::context::single_dh_use);

    ctx.use_certificate_chain(
        boost::asio::buffer(cert.data(), cert.size()));

    ctx.use_private_key(
        boost::asio::buffer(key.data(), key.size()),
        boost::asio::ssl::context::file_format::pem);

    ctx.use_tmp_dh(
        boost::asio::buffer(dh.data(), dh.size()));
}

#endif