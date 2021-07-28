package m19;

/**
 * Enum for work categories
 */
enum Category {

    REFERENCE {
        @Override
        @SuppressWarnings("nls")
        public String toString(){ return "Referência"; }
    },

    FICTION {
        @Override
        @SuppressWarnings("nls")
        public String toString(){ return "Ficção"; }
    },

    SCITECH {
        @Override
        @SuppressWarnings("nls")
        public String toString(){ return "Técnica e Científica"; }
    }
}