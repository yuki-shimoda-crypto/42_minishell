#minishell

## Issue
- [github_issue](https://github.com/yuki-shimoda-crypto/42_minishell/issues)

## Flow
1. Input
    1. readline 
    1. add_history
1. Tokenize
    1. consume_blank
    1. is_operator
    1. is_word
        1. if (c == single quote || c == double quote) つぎのクォートまでインプット
1. parse
    1. remove sigle quote
    1. remove double quote
    1. redirect
1. exec
    1. search_path
    1. validate_access
    1. execve
1. expand
    1. single_quote
        1. 次のsingle quoteまでをinput
    1. double_quote
        1. 次のdouble quoteまでをinput
        1. if $WORD expand $WORD
    1. $WORD
        1. $?
        1. expand $WORD
1. signal
    1. setup_signal
        1. rl_event_hookに呼び出す関数(signal_hook)を設定する 
        1. signal(SIGINT, ctrl_c)(sigintが来たときの処理)
        1. ignore_sigquit
        ```c
        void setup_signal(void)
        {
            rl_event_hook = signal_hook;
            rl_outstream = stderr;
            signal(SIGINT, ctrl_c);
            signal(SIGQUIT, ctrl_backslash);
        }
        ```
    1. int  signal_hook(int g_sig)
        ```c
		int signal_hook(int g_sig)
        {
            if (g_sig == 0)
                return (0);
            else if (g_sig == SIGINT)
            {
                g_sig = 0;
                rl_replace_line("", 0);
                rl_done = 1;
            }
            return (0);
        }
        ```
    1. int ctrl_c(int sig)
        ```c
        int ctrl_c(int sig)
        {
            g_sig = sig;
        }
        ```
    1. int ignore_sigquit(int sig)
        ```c
        ```

## struct
```
typedef enum e_tk_kind t_tk_kind;
enum e_tk_kind
{
    TK_WORD,
    TK_OPERATOR,
    TK_EOF,
};
```

```
typedef struct s_tk t_tk;
struct s_tk
{
    char			*word;
	t_tk_kind		kind;
    struct s_token	*next;
};
```

```
typedef enum e_node_kind t_node_kind;
enum e_node_kind
{
    ND_PIPE,
    ND_SIMPLE_CMD,
    ND_REDIRECT_OUT,
    ND_REDIRECT_IN,
    ND_REDIRECT_APPEND,
    ND_REDIRECT_HEREDOC,
}
```

```
typedef struct s_node t_node;
struct s_node
{
	t_node_kind	kind;
    t_node		*next;
    // CMD
	t_node	*command;
    // REDIRECT
	t_node	*redirect;
	t_token	*filename;
	t_token	*delimiter;
	int		filefd;
}
```

```
typedef struct s_env t_env;
struct s_env
{
	char		*key;
	char		*value;
	t_env		*pre;
	t_env		*next;
}
```


## Rule
- Only if original function exists add "ft" at head of the function

## Link_Minishell
- [subject_pdf](https://cdn.intra.42.fr/pdf/pdf/65564/en.subject.pdf)
- [github](https://github.com/yuki-shimoda-crypto/42_minishell)
- [The Architecture of Open Source Applications](https://aosabook.org/en/index.html)
- [The Architecture of Open Source Applications_日本語版](https://github.com/m-takagi/aosa-ja)
- [bash original](https://savannah.gnu.org/projects/bash/#devtools)
- [bash original git](https://savannah.gnu.org/git/?group=bash)
- [minishellの作り方_宇佐美さん](https://usatie.notion.site/minishell-29921d3ea13447ad897349acd5733d5e)
- [minishell_jtanaka](https://jun-networks.hatenablog.com/entry/2021/07/02/034002)
- [minishell_rakiyama](https://rakiyama0229.hatenablog.jp/entry/2021/10/05/120920)

## Link_Tips
- [C11言語仕様の最終ドラフト（公式の規格書と内容は同一）](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
- [CERT C コーディングスタンダード](https://www.jpcert.or.jp/sc-rules/)
- [APUE(詳解UNIXプログラミング)](http://apuebook.com/apue3e.html)
- [The Linux Programming Interface(TLPI)](https://www.man7.org/)
- [低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook)


## Link_Other
- [知らないと恥ずかしいコードレビューで指摘されがちなポイント14選](https://qiita.com/ouauai/items/d38eeef9f0af5a4a87da)
- [Vimで高速で移動~プラグインなしでの移動まとめ](https://qiita.com/takeharu/items/9d1c3577f8868f7b07b5)
- [C言語　__attribute__((destructor))を使用したメモリリークチェックツール](https://zenn.dev/keitean/articles/ad82c4bbfe434a)
- [gitを使った開発](https://qiita.com/keitean/items/eb0f00cb13d29c624ab1)
- [github通知の削除](https://github.com/settings/notifications)
- [2020_nop_advent_calender](https://nop42.medium.com/42tokyo%E3%81%AE%E7%94%9F%E5%BE%92%E3%81%9F%E3%81%A1%E3%81%AE%E4%B8%8D%E6%80%9D%E8%AD%B0%E3%81%AA%E3%82%B3%E3%83%9F%E3%83%83%E3%83%88%E5%B1%A5%E6%AD%B4%E9%9B%86-406928cddfa1)

## Link_Discord
- [シェルの多段パイプを自作してみる](https://keiorogiken.wordpress.com/2017/12/15/%E3%82%B7%E3%82%A7%E3%83%AB%E3%81%AE%E5%A4%9A%E6%AE%B5%E3%83%91%E3%82%A4%E3%83%97%E3%82%92%E8%87%AA%E4%BD%9C%E3%81%97%E3%81%A6%E3%81%BF%E3%82%8B/)
- [man bash](https://linuxjm.osdn.jp/html/GNU_bash/man1/bash.1.html)
- [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [C言語の学習にちょうど良いものを見つけた(Tutorial - Write a Shell in C)](https://diary.shuichi.tech/entry/2017/03/31/225633)
- [入門 シェル実装](https://www.slideshare.net/yusukesangenya/ss-135407412)
- [プロセスの作成 fork](https://kaworu.jpn.org/c/%E3%83%97%E3%83%AD%E3%82%BB%E3%82%B9%E3%81%AE%E4%BD%9C%E6%88%90_fork)
- [シェル変数と環境変数の違い（bash）](https://qiita.com/Kotabrog/items/144e6e314ce82fb3f683)
- [良いコードとは何か - エンジニア新卒研修 スライド公開](https://note.com/cyberz_cto/n/n26f535d6c575#E0aBe)
- [Linux上でシェルが実行される仕組みを，体系的に理解しよう　（bash 中級者への道）](https://language-and-engineering.hatenablog.jp/entry/20110617/p1)
- [システムプログラム（第3週）](http://www.coins.tsukuba.ac.jp/~syspro/2005/No3.html)
- [ファイル操作とファイル・システム](https://ie.u-ryukyu.ac.jp/~kono/os/ex/file/file.html)
- [C言語で環境変数を扱うことにフォーカスした内容](https://github.com/y-uchiida/clang-training/blob/main/environment-variables_in_c/commentary.md)
- [pipeを作ってforkしてexec](https://github.com/brenns10/lsh/tree/9f2b98a74992f2837903f0ed91f4c6cb69784ab4)

## Link_Community
- [connpass](https://connpass.com/)
- [meety](https://meety.net/)

## memo
### memo
- なぜ、test.shのassert()内で、echo -nをつけて、最後にechoをしているのか
- pipeのときのredirectを優先するときの判定を見てもらいたい。しっかりとつながっているのか`
		if (!is_redirect_out_exist(node))
		if (!is_redirect_in_exist(node))
- ls | unset PATH おもろかった write失敗する

- ccache消しても良いかも

## vim 
- ctrl + gでファイルの情報の閲覧
- ctrl + pで前方置換
- ctrl + nで後方置換
- {は空白行を目印に移動
- %は対応するかっこまで飛ぶ
- ~は小文字と大文字を相互に変換
- *はカーソルのある単語を検索
- =は範囲を自分で選んで自動インデント
- Jはカーソル行のある行を次の行と結合
- zfでたためる
- zoで開く
- z0ですべて開く
- zcで閉じる
- zCですべて閉じる 
- :split(sp) 水平分割
- :vsplit(vsp) 垂直分割
- :reg "2pみたいな感じで使う
- :waは開いているファイルをすべて保存
- :Exはvim標準のエクスプローラーを開く
- 挿入モードでctrl + tインデント追加
- 挿入モードでctrl + bインデント追加
- manを見たい時にはShift+kでカーソルのmanを見ることができる。man 2 に飛びたい時は、2 Shift+kにする
- カーソルをヘッダーファイルの上にしてから、gfを押すとヘッダーファイルに飛ぶことができる ctrl-oで閉じる。Ctrl-w gfで開いて、gfをすれば良いタブの動き方はgt
- set lines=100
- set columns=300
- {count}ctrl-w + '+' ウィンドウの高さを広げる
- {count}ctrl-w + '-' ウィンドウの高さを狭める
- ctrl-w + '_' ウィンドウの高さを最大にする
- ctrl-w + '>' ウィンドウの幅を広げる
- ctrl-w + '<' ウィンドウの幅を狭める
- ctrl-w + '|' ウィンドウの幅を最大に広げる
- vertical resize {count}
- vert res {count}
- z{count}
- ctrl + '=' ウィンドウのサイズを揃える
- zz 現在の行を中央にする
- zt 現在の行を一番上にする
- zb 現在の行を一番下にする
- Esc ctrl + [ ctrl + c ctrl + n ctrl + \
- ctrl + o ジャンプリストの[count]個古いカーソル位置に移動
- ctrl + i ジャンプリストの[count]個新しいカーソル位置に移動
- 挿入モードでctrl + a直前に入力したテキストの再挿入
- 挿入モードでctrl + w単語の削除
- 挿入モードでctrl + u行の削除
- 挿入モードでctrl + tタブの挿入
- 挿入モードでctrl + dタブの削除
- レジスタ "無名レジスタ
- レジスタ _削除用レジスタ
- レジスタ a-z名前付きレジスタ
- レジスタ = expression用レジスタ
- ctags **/*.c **/*.h


## 使用可能関数
access
add_history
chdir
close
closedir
dup
dup2
execve
exit
fork
free
fstat
getcwd
getenv
ioctl
isatty
kill
lstat
malloc
open
opendir
perror
pipe
printf
read
readdir
readline
rl_clear_history
rl_on_new_line
rl_redisplay
rl_replace_line
sigaction
sigaddset
sigemptyset
signal
stat
strerror
tcgetattr
tcsetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
ttyname
ttyslot
unlink
wait
wait3
wait4
waitpid
write

