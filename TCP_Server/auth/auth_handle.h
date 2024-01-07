
enum AuthStatus
{
    LOGIN_SUCCESS,
    LG_USER_BLOCK,
    LG_USER_NOT_EXIST,
    INCORRECT_PASSWORD,
    LG_OTHER_CLIENT,
};

/**
 * @function check_auth: Read the account information file and check the state of account
 *
 * @param username: username
 * @param password: password
 *
 * @return :LOGIN_SUCCESS if success
 *          LG_USER_BLOCK if account is banned
 *          LG_USER_NOT_EXIST if account is not found
 *          WRONG_PASSWORD if input wrong password
 */
enum AuthStatus login_handle(char *username, char *password);
int check_account_exist();
// void logout_handle();
int signup_handle();