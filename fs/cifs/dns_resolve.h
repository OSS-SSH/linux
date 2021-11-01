/* SPDX-License-Identifier: LGPL-2.1 */
/*
<<<<<<< HEAD
 *   DNS Resolver upcall management for CIFS DFS
 *   Handles host name to IP address resolution
=======
 *   fs/cifs/dns_resolve.h -- DNS Resolver upcall management for CIFS DFS
 *                            Handles host name to IP address resolution
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
 *
 *   Copyright (c) International Business Machines  Corp., 2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 */

#ifndef _DNS_RESOLVE_H
#define _DNS_RESOLVE_H

#ifdef __KERNEL__
<<<<<<< HEAD
extern int dns_resolve_server_name_to_ip(const char *unc, char **ip_addr, time64_t *expiry);
=======
extern int dns_resolve_server_name_to_ip(const char *unc, char **ip_addr);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif /* KERNEL */

#endif /* _DNS_RESOLVE_H */
